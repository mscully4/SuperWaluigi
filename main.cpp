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

using namespace std;

int main() {
	int window_width = sf::VideoMode().getDesktopMode().width;
    int window_height = sf::VideoMode().getDesktopMode().height;
    //int window_width = 1250;
	//int window_height = 600;
	const int tile_width = 32;
	const int tile_height = 32;
	const double map_scale = 2;
	vector<vector<int>> level;
	load_map("Assets/map/1-1.txt", level);
	const int map_rows = level[0].size();
	const int map_columns = level.size();
	double map_width = map_rows * tile_width * map_scale;
	double map_height = map_columns * tile_height * map_scale;
	int time_left = 400;
	int time_elapsed;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Super Waluigi");

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window_width, window_height));
	sf::Clock game_clock;
	sf::Clock timer;

    vector<PowerUp> power_ups;
    Player player("Assets/images/rsz_waluigi_jacked.png", 0, 0, 63, 125);

	Goomba goomba1("Assets/images/Goomba.png", 400, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba2("Assets/images/Goomba.png", 1000, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba3("Assets/images/Goomba.png", 2180, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba4("Assets/images/Goomba.png", 2750, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba5("Assets/images/Goomba.png", 3700, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba6("Assets/images/Goomba.png", 5800, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba7("Assets/images/Goomba.png", 8700, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba8("Assets/images/Goomba.png", 9500, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);

	sf::SoundBuffer loser_buffer;
	loser_buffer.loadFromFile("Assets/sounds/loser.wav");
	sf::Sound loser;
	loser.setBuffer(loser_buffer);

	Ending ending("Assets/images/SpriteSheet2.png", 4, 4, map_width, map_height);

	sf::Font consola_font;
	consola_font.loadFromFile("Assets/fonts/Pixel Emulator.otf");
	
	sf::Text text_waluigi("WALUIGI", consola_font, 20);
	text_waluigi.setFillColor(sf::Color(255, 255, 255));
	sf::Text text_world("WORLD", consola_font, 20);
	sf::Text text_level("1-1", consola_font, 20);
	sf::Text text_time("TIME", consola_font, 20);
	sf::Text text_seconds("400", consola_font, 20);


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		TileMap map("Assets/images/SpriteSheet2.png", level, tile_width, tile_height);
		map.scale(map_scale, map_scale);


		double fps = game_clock.restart().asMilliseconds();
		time_elapsed = timer.getElapsedTime().asSeconds();
		text_seconds.setString(to_string(time_left - time_elapsed));

		view.setCenter(sf::Vector2f(player.m_center_pos[0], player.m_center_pos[1]));

		player.update(fps, map_rows, map_columns, tile_width, tile_height, map_scale, level, power_ups);
        //cout << player.get_big() << endl;        

		goomba1.update(fps, map_rows, map_columns, &player, level);
		goomba2.update(fps, map_rows, map_columns, &player, level);
		goomba3.update(fps, map_rows, map_columns, &player, level);
		goomba4.update(fps, map_rows, map_columns, &player, level);
		goomba5.update(fps, map_rows, map_columns, &player, level);
		goomba6.update(fps, map_rows, map_columns, &player, level);
		goomba7.update(fps, map_rows, map_columns, &player, level);
		goomba8.update(fps, map_rows, map_columns, &player, level);

		if (player.m_center_pos[0] > 0 + (window_width/2) && player.m_center_pos[0] < (map_rows * tile_width * map_scale) - (window_width/2)) {
			view.setCenter(sf::Vector2f(player.m_center_pos[0], (map_height + (map_height - window_height)) / 2));
	        text_waluigi.setPosition(player.m_center_pos[0] - (.4 * window_width), 310);
            text_world.setPosition(player.m_center_pos[0] + (.1 * window_width), 310);
			text_level.setPosition(player.m_center_pos[0] + 20 + (.1 * window_width), 340);
	        text_time.setPosition(player.m_center_pos[0] + (.35 * window_width), 310);
            text_seconds.setPosition(player.m_center_pos[0] + (.35 * window_width), 340);
		} else if (player.m_center_pos[0] < 0 + (window_width / 2)) {
			view.setCenter(sf::Vector2f((window_width / 2), (map_height + (map_height - window_height)) / 2));
	        text_waluigi.setPosition(120, 310);
	        text_world.setPosition(720, 310);
			text_level.setPosition(740, 340);
			text_time.setPosition(1020, 310);
			text_seconds.setPosition(1020, 340);
		} else if (player.m_center_pos[0] > (map_rows * tile_width * map_scale) - (window_width / 2)) {
			view.setCenter(sf::Vector2f(player.m_center_pos[0], (map_height + (map_height - window_height)) / 2));
	        text_waluigi.setPosition(player.m_center_pos[0] - (.1 * window_width), 310);
	        text_world.setPosition(player.m_center_pos[0] + (.1 * window_width), 310);
			text_level.setPosition(player.m_center_pos[0] + 20 + (.1 * window_width), 340);
	        text_time.setPosition(player.m_center_pos[0] + (.35 * window_width), 310);
            text_seconds.setPosition(player.m_center_pos[0] + (.35 * window_width), 340);
	}

		window.setView(view);
		window.clear(sf::Color(80,128,255));
		window.draw(map);
		window.draw(player);
		window.draw(goomba1);
		window.draw(goomba2);
		window.draw(goomba3);
		window.draw(goomba4);
		window.draw(goomba5);
		window.draw(goomba6);
		window.draw(goomba7);
		window.draw(goomba8);
		window.draw(ending);
        for (int i=0; i < power_ups.size(); ++i) {
            if (power_ups[i].get_active()) {
                window.draw(power_ups[i]);
            }
        }

		window.draw(text_waluigi);
		window.draw(text_world);
		window.draw(text_level);
		window.draw(text_time);
		window.draw(text_seconds);
		
		window.display();
		
        if(!player.get_alive() || time_elapsed > time_left){
			loser.play();
			this_thread::sleep_for(chrono::seconds(2));
			window.close();
		}
	}
	return 0;
}
