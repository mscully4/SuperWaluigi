#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include "load_map.cpp"
#include "Entity.h"
#include "Player.h"
#include "TileMap.h"
#include "Enemies.h"
#include "Ending.h"
#include "PowerUp.h"
#include "Chork.h"

using namespace std;

int main() {
    int window_width = 1200;
	int window_height = 600;
	const int tile_width = 64;
	const int tile_height = 64;
	const double map_scale = 1;
    vector<vector<int>> level;
    vector<int> power_up_counter = {0, 0, 0};
    load_map("Assets/map/1-1.txt", level, power_up_counter);
    cout << "Mushrooms: " << power_up_counter[0] << " Chorks: " << power_up_counter[1] << " Stars: " << power_up_counter[2] << endl;

    const int map_rows = level[0].size();
	const int map_columns = level.size();
	double map_width = map_rows * tile_width * map_scale;
	double map_height = map_columns * tile_height * map_scale;
	int time_left = 400;
	int time_elapsed;
    int coins;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Super Waluigi");

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window_width, window_height));
    Ending ending("Assets/images/SpriteSheet2.png", 4, 4, map_width, map_height);


    Chork chork("Assets/images/Vomit.png", 0, 0, 70, 44);

    vector<vector<PowerUp>> created_power_ups = {{}, {}, {}};
    for (int i=0; i<power_up_counter[0]; ++i) {
        created_power_ups[0].push_back(PowerUp("Assets/images/Mushroom.png", tile_width, tile_height, "Mushroom"));
    }
    for (int i=0; i<power_up_counter[1]; ++i) {
        created_power_ups[1].push_back(PowerUp("Assets/images/Chork.png", tile_width, tile_height, "Chork"));
    }
    for (int i=0; i<power_up_counter[2]; ++i) {
        created_power_ups[2].push_back(PowerUp("Assets/images/Star.png", tile_width, tile_height, "Star"));
    }
    vector<PowerUp> active_power_ups;
    
    Player player("Assets/images/WaluigiSpriteSheet.png", 100, 100, chork, created_power_ups);
    
    vector<Goomba> goombas;
	goombas.push_back(Goomba("Assets/images/Goomba.png", 400, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
    goombas.push_back(Goomba("Assets/images/Goomba.png", 1000, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
    goombas.push_back(Goomba("Assets/images/Goomba.png", 2180, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
	goombas.push_back(Goomba("Assets/images/Goomba.png", 2750, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
	goombas.push_back(Goomba("Assets/images/Goomba.png", 3700, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
	goombas.push_back(Goomba("Assets/images/Goomba.png", 5800, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
	goombas.push_back(Goomba("Assets/images/Goomba.png", 8700, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));
	goombas.push_back(Goomba("Assets/images/Goomba.png", 9500, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale));

	sf::SoundBuffer loser_buffer;
	loser_buffer.loadFromFile("Assets/sounds/loser.wav");
	sf::Sound loser;
	loser.setBuffer(loser_buffer);


	sf::Font consola_font;
	consola_font.loadFromFile("Assets/fonts/Pixel Emulator.otf");
	
	sf::Text text_waluigi("WALUIGI", consola_font, 20);
	text_waluigi.setFillColor(sf::Color(255, 255, 255));
	sf::Text text_world("WORLD", consola_font, 20);
	sf::Text text_level("1-1", consola_font, 20);
	sf::Text text_time("TIME", consola_font, 20);
	sf::Text text_seconds("400", consola_font, 20);
    sf::Text text_coins("00", consola_font, 20);

    Entity coin_icon;
    coin_icon.m_texture.loadFromFile("Assets/images/Coin.png");
    coin_icon.m_vertices.setPrimitiveType(sf::Quads);
    coin_icon.m_vertices.resize(32 * 32 * 4);
    coin_icon.m_vertices[0].texCoords = sf::Vector2f(0, 0);
    coin_icon.m_vertices[1].texCoords = sf::Vector2f(32, 0);
    coin_icon.m_vertices[2].texCoords = sf::Vector2f(32, 32);
    coin_icon.m_vertices[3].texCoords = sf::Vector2f(0, 32);
	
    sf::Clock timer;
	sf::Clock game_clock;
    	
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		TileMap map("Assets/images/Tiles.png", level, tile_width, tile_height);

        double fps = game_clock.restart().asMilliseconds();
        if (fps > 10) {
            fps = 10;
        }

		time_elapsed = timer.getElapsedTime().asSeconds();
		text_seconds.setString(to_string(time_left - time_elapsed));
	    view.setCenter(sf::Vector2f(player.m_center_pos[0], player.m_center_pos[1]));
        
        player.update(fps, map_rows, map_columns, tile_width, tile_height, map_scale, level, active_power_ups, chork);
        
        coins = player.get_coins();
        if (coins > 10) {
            text_coins.setString("X " + to_string(coins));
        } else {
            text_coins.setString("X 0" + to_string(coins));
        }
        for (int i = 0; i < goombas.size(); ++i) {
		    goombas[i].update(fps, map_rows, map_columns, &player, &chork, level);
		}
	 
        if (player.m_center_pos[0] < 0 + (window_width / 2)) {
			view.setCenter(sf::Vector2f((window_width / 2), (map_height + (map_height - window_height)) / 2));
	        text_waluigi.setPosition(120, 310);
            text_coins.setPosition(480, 310);
	        text_world.setPosition(720, 310);
			text_level.setPosition(740, 340);
			text_time.setPosition(1020, 310);
			text_seconds.setPosition(1020, 340);
	        coin_icon.m_vertices[0].position = sf::Vector2f(420, 306);
            coin_icon.m_vertices[1].position = sf::Vector2f(452, 306);
            coin_icon.m_vertices[2].position = sf::Vector2f(452, 338);
            coin_icon.m_vertices[3].position = sf::Vector2f(420, 338);
	    } else {
			view.setCenter(sf::Vector2f(player.m_center_pos[0], (map_height + (map_height - window_height)) / 2));
	        text_waluigi.setPosition(player.m_center_pos[0] - (.4 * window_width), 310);
	        text_coins.setPosition(player.m_center_pos[0] - (.1 * window_width), 310);
            text_world.setPosition(player.m_center_pos[0] + (.1 * window_width), 310);
			text_level.setPosition(player.m_center_pos[0] + 20 + (.1 * window_width), 340);
	        text_time.setPosition(player.m_center_pos[0] + (.35 * window_width), 310);
            text_seconds.setPosition(player.m_center_pos[0] + (.35 * window_width), 340);
            coin_icon.m_vertices[0].position = sf::Vector2f(player.m_center_pos[0] - (window_width * .15), 306);
            coin_icon.m_vertices[1].position = sf::Vector2f(player.m_center_pos[0] + 32 - (window_width * .15), 306);
            coin_icon.m_vertices[2].position = sf::Vector2f(player.m_center_pos[0] + 32 - (window_width * .15), 338);
            coin_icon.m_vertices[3].position = sf::Vector2f(player.m_center_pos[0] - (window_width * .15), 338);

	    }
		
        window.setView(view);
		window.clear(sf::Color(80,128,255));
		window.draw(map);
		window.draw(ending);
		window.draw(player);
        window.draw(chork);
        
        for (int i = 0; i < goombas.size(); ++i) {
		    window.draw(goombas[i]);
        }

        for (int i=0; i < active_power_ups.size(); ++i) {
            if (active_power_ups[i].get_show()) {
                window.draw(active_power_ups[i]);
             }
        }

		window.draw(text_waluigi);
        window.draw(coin_icon);
        window.draw(text_coins);
		window.draw(text_world);
		window.draw(text_level);
		window.draw(text_time);
		window.draw(text_seconds);
		window.display();
		
        if(!player.get_alive() || time_elapsed > time_left) {
            loser.play();
			this_thread::sleep_for(chrono::seconds(2));
			window.close();
		} else if (player.get_complete()) {
            //this_thread::sleep_for(chrono::milliseconds(1600));
            window.close();
        }
	}
	return 0;
}
