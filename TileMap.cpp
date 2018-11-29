#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <iostream>
#include <vector>

using namespace std;

TileMap::TileMap(const string& sprite_sheet, vector<vector<int>>& level, const int tile_width, const int tile_height) {

	m_texture.loadFromFile(sprite_sheet);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(level.size() * level[0].size() * 4);
	sf::Vector2u tile_size(tile_width, tile_height);
	for (int i = 0; i < level.size(); ++i) {
		for (int j = 0; j < level[0].size(); ++j) {
			sf::Vertex* quad = &m_vertices[(i + j * level.size()) * 4];

			if (level[i][j]) {
			quad[0].position = sf::Vector2f(j * tile_size.x, i * tile_size.y);
			quad[1].position = sf::Vector2f((j + 1) * tile_size.x, i * tile_size.y);
			quad[2].position = sf::Vector2f((j + 1) * tile_size.x, ((i + 1) * tile_size.y));
			quad[3].position = sf::Vector2f(j * tile_size.x, ((i + 1) * tile_size.y));

			quad[0].texCoords = sf::Vector2f(0, 0);
			quad[1].texCoords = sf::Vector2f(tile_size.x, 0);
			quad[2].texCoords = sf::Vector2f(tile_size.x, tile_size.y);
			quad[3].texCoords = sf::Vector2f(0, tile_size.y);
			}
		}
	}
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
