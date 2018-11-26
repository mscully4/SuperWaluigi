#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Tile.h"

Tile::Tile(const std::string& textureFile, double x_pos, double y_pos, double tile_width, double tile_height, double texture_x, double texture_y) {
	m_scale[0] = 3.0f;
	m_scale[1] = 3.0f;

	m_transform.scale(sf::Vector2f(m_scale[0], m_scale[1]));

	m_texture.loadFromFile(textureFile, sf::IntRect(texture_x, texture_y, tile_width, tile_height));
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(tile_width * tile_height * 4);

	

	m_vertices[0].position = sf::Vector2f(x_pos, y_pos);
	m_vertices[1].position = sf::Vector2f(x_pos + tile_width, y_pos);
	m_vertices[2].position = sf::Vector2f(x_pos + tile_width, y_pos + tile_height);
	m_vertices[3].position = sf::Vector2f(x_pos, y_pos + tile_height);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(tile_width, 0);
	m_vertices[2].texCoords = sf::Vector2f(tile_width, tile_height);
	m_vertices[3].texCoords = sf::Vector2f(0, tile_height);

	m_obs_size[0] = m_vertices[1].position.x - m_vertices[0].position.x;
	m_obs_size[1] = m_vertices[3].position.y - m_vertices[0].position.y;
	m_half_size[0] = m_obs_size[0] / 2;
	m_half_size[1] = m_obs_size[1] / 2;
	m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
	m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];
}

