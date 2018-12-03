#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "TileMap.h"
#include "Enemies.h"
#include "Ending.h"

using namespace std;

int main() {
	int window_width = 1200;
	int window_height = 600;
	const int tile_width = 32;
	const int tile_height = 32;
	const double map_scale = 2;
vector<vector<int>> level {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,2,2,2,3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,2,3,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,9,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3,0,0,3,0,0,3,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,4,0,0,0,0,0,2,2,3,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,4,0,0,0,0,0,0,0,4,4,4,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,9,0,0,0,0,0,0,6,7,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,4,4,0,0,0,0,0,4,4,4,4,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,6,7,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,4,4,4,0,0,0,4,4,4,4,4,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	const int map_rows = level[0].size();
	const int map_columns = level.size();
	double map_width = map_rows * tile_width * map_scale;
	double map_height = map_columns * tile_height * map_scale;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Super Waluigi");

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window_width, window_height));
	sf::Clock game_clock;

	Player player("Assets/images/Waluigi.png", 0, 0, 58, 106);

	Goomba goomba1("Assets/images/GOOMBA.png", 400, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba2("Assets/images/GOOMBA.png", 1000, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba3("Assets/images/GOOMBA.png", 2180, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba4("Assets/images/GOOMBA.png", 2750, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba5("Assets/images/GOOMBA.png", 3700, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba6("Assets/images/GOOMBA.png", 5800, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba7("Assets/images/GOOMBA.png", 8700, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);
	Goomba goomba8("Assets/images/GOOMBA.png", 9500, 0, 64, 64, map_width, map_height, tile_width, tile_height, map_scale);




	Ending ending("Assets/images/SpriteSheet2.png", 4, 4, map_width, map_height);
	//ending.scale(2, 2);

	sf::Font consola_font;
	if (!consola_font.loadFromFile("Assets/fonts/consola.ttf")) cout << "FEIHEOIFHEWOIEH" << endl;
	sf::Text lives("Lives: ", consola_font, 50);
	lives.setPosition(175, 300);
	//lives.setColor(sf::Color(33, 44, 55));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		TileMap map("Assets/images/SpriteSheet2.png", level, tile_width, tile_height);
		map.scale(map_scale, map_scale);

		lives.setString("Lives Remaining: " + to_string(player.lives));

		double fps = game_clock.restart().asMilliseconds();
		float delta_time = game_clock.getElapsedTime().asSeconds();
		view.setCenter(sf::Vector2f(player.m_center_pos[0], player.m_center_pos[1]));

		player.update(fps, map_rows, map_columns, tile_width, tile_height, map_scale, level);

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
		} else if (player.m_center_pos[0] < 0 + (window_width / 2)) {
			view.setCenter(sf::Vector2f((window_width / 2), (map_height + (map_height - window_height)) / 2));
		} else if (player.m_center_pos[0] > (map_rows * tile_width * map_scale) - (window_width / 2)) {
			view.setCenter(sf::Vector2f(player.m_center_pos[0], (map_height + (map_height - window_height)) / 2));
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
		window.draw(lives);

		window.display();
		if(player.lives < 0){
			window.close();
		}
	}
	return 0;
}
