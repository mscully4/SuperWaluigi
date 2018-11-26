#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <iostream>
#include <vector>

TileMap::TileMap(const int map_width, const int map_height, const int tile_width, const int tile_height) {

	m_texture.loadFromFile("Assets/images/Floor_Tile1.png");

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(map_width * map_height * 4);
	level = { {0, 0}, {0, 0} };
	sf::Vector2u tile_size(tile_width, tile_height);
	for (int i = 0; i < map_width; ++i) {
		for (int j = 0; j < map_height; ++j) {
			sf::Vertex* quad = &m_vertices[(i + j * map_width) * 4];

			//quad[0].position = sf::Vector2f(i * tile_size.x, (j * tile_size.y));
			//quad[1].position = sf::Vector2f((i + 1) * tile_size.x, (j * tile_size.y));
			//quad[2].position = sf::Vector2f((i + 1) * tile_size.x, ((j + 1) * tile_size.y));
			//quad[3].position = sf::Vector2f(i * tile_size.x, ((j + 1) * tile_size.y));

			if (j == 9) {
				quad[0].position = sf::Vector2f(i * tile_size.x, (j * tile_size.y));
				quad[1].position = sf::Vector2f((i + 1) * tile_size.x, (j * tile_size.y));
				quad[2].position = sf::Vector2f((i + 1) * tile_size.x, ((j + 1) * tile_size.y));
				quad[3].position = sf::Vector2f(i * tile_size.x, ((j + 1) * tile_size.y));

				quad[0].texCoords = sf::Vector2f(0, 0);
				quad[1].texCoords = sf::Vector2f(tile_size.x, 0);
				quad[2].texCoords = sf::Vector2f(tile_size.x, tile_size.y);
				quad[3].texCoords = sf::Vector2f(0, tile_size.y);
			}/*
			 else {
				quad[0].texCoords = sf::Vector2f(tile_size.x, tile_size.y);
				quad[1].texCoords = sf::Vector2f(tile_size.x * 2, tile_size.y);
				quad[2].texCoords = sf::Vector2f(tile_size.x * 2, tile_size.y * 2);
				quad[3].texCoords = sf::Vector2f(tile_size.x, tile_size.y * 2);
			}
			 */
		}
	}
	//map = { {tile1, tile2}, {tile3, tile4} };
};

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_texture;

		// draw the vertex array
		target.draw(m_vertices, states);
	}
