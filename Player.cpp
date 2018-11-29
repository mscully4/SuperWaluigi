#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace std; 

Player::Player(const std::string& textureFile, double x_pos, double y_pos, double image_width, double image_height) {
	sprite_width = image_width;
	sprite_height = image_height;

	m_scale[0] = 1.0f;
	m_scale[1] = 1.0f;

	m_texture.loadFromFile(textureFile);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(image_width * image_height * 4);

	m_vertices[0].position = sf::Vector2f(x_pos, y_pos);
	m_vertices[1].position = sf::Vector2f(x_pos + image_width, y_pos);
	m_vertices[2].position = sf::Vector2f(x_pos + image_width, y_pos + sprite_height);
	m_vertices[3].position = sf::Vector2f(x_pos, y_pos + image_height);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(image_width, 0);
	m_vertices[2].texCoords = sf::Vector2f(image_width, image_height);
	m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);

	m_obs_size[0] = m_vertices[1].position.x - m_vertices[0].position.x;
	m_obs_size[1] = m_vertices[3].position.y - m_vertices[0].position.y;
	m_half_size[0] = m_obs_size[0] / 2;
	m_half_size[1] = m_obs_size[1] / 2;
	m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
	m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];

	//std::cout << m_obs_size[0] << ", " << m_obs_size[1] << std::endl;

	x_vel = 0.0f;
	y_vel = 0.0f;

}

void Player::update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale) {
	key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	key_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

	if (key_left) {
		x_vel = -1;
		m_vertices[0].texCoords = sf::Vector2f(sprite_width, 0);
		m_vertices[1].texCoords = sf::Vector2f(0, 0);
		m_vertices[2].texCoords = sf::Vector2f(0, sprite_height);
		m_vertices[3].texCoords = sf::Vector2f(sprite_width, sprite_height);
	}
	if (key_up) {
		y_vel = -1;
	}
	if (key_down) {
		y_vel = 1;
	}
	if (key_right) {
		x_vel = 1;
		m_vertices[0].texCoords = sf::Vector2f(0, 0);
		m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
		m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
		m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);
	}

	if (!key_left && !key_right) {
		x_vel = 0;
	}
	if (!key_down && !key_up) {
		y_vel = 1;
	}

	if (m_vertices[0].position.x + (x_vel * delta_time) >= 0 && m_vertices[2].position.x + (x_vel * delta_time) <= map_width * tile_width * map_scale) {
		for (int i = 0; i < 4; ++i) {
			m_vertices[i].position.x += x_vel * delta_time;
		}
	}
	if (m_vertices[0].position.y + (y_vel * delta_time) >= 0 && m_vertices[2].position.y + (y_vel * delta_time) <= (map_height - 1) * tile_height  * map_scale) {
		for (int i = 0; i < 4; ++i) {
			m_vertices[i].position.y += y_vel * delta_time;
		}
	}


	m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
	m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];
}
