#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "TileMap.h"
#include "Enemies.h"

using namespace std;

int main() {
	int window_width = 1260;
	int window_height = 600;
	const int tile_width = 32;
	const int tile_height = 32;
	const double map_scale = 2;
	vector<vector<int>> level = { {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
		  {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
		  {1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
		  {1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		  {0, 0, 1, 1, 0, 1, 0, 0, 1, 0},
		  {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		  {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
		  {1, 1, 0, 0, 0, 1, 1, 0, 1, 1},
		  {0, 1, 0, 1, 1, 0, 0, 1, 0, 1} };
	const int map_rows = level.size();
	const int map_columns = level[0].size();
	double map_width = map_rows * tile_width * map_scale;
	double map_height = map_columns * tile_height * map_scale;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Super Waluigi");

	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(window_width, window_height));
	sf::Clock game_clock;

	sf::Font consola_font;
	consola_font.loadFromFile("Assets/fonts/consola.ttf");
	sf::Text hello("Hello", consola_font, 50);

	Player player("Assets/images/Waluigi1.png", 0, 300, 29, 53);

	Goomba goomba1("Assets/images/GOOMBA.png", 500, 100, 40, 48, map_width, map_height, tile_width, tile_height, map_scale);

	TileMap map("Assets/images/Floor_Tile1.png", level, tile_width, tile_height);
	map.scale(map_scale, map_scale);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		double fps = game_clock.restart().asMilliseconds();
		float delta_time = game_clock.getElapsedTime().asSeconds();

		view.setCenter(sf::Vector2f(player.m_center_pos[0], player.m_center_pos[1]));

		player.update(fps, map_rows, map_columns, tile_width, tile_height, map_scale);
		goomba1.update(fps, &player);
		/*if (player.m_center_pos[0] > 0 + (window_width/2) && player.m_center_pos[0] < (map_rows * tile_width * map_scale) - (window_width/2)) {
			view.setCenter(sf::Vector2f(player.m_center_pos[0], (map_height + (map_height - window_height)) / 2));
		} else if (player.m_center_pos[0] < 0 + (window_width / 2)) {
			view.setCenter(sf::Vector2f((window_width / 2), (map_height + (map_height - window_height)) / 2));
		} else if (player.m_center_pos[0] > (map_rows * tile_width * map_scale) - (window_width / 2)) {
			view.setCenter(sf::Vector2f((map_rows * tile_width * map_scale) - (window_width / 2), (map_height + (map_height - window_height)) / 2));
		}*/


		window.setView(view);
		window.clear(sf::Color(89, 143, 244));
		window.draw(map);
		window.draw(player);
		window.draw(goomba1);

		window.display();
	}
	return 0;
}
