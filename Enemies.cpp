#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Enemies.h"
#include "Player.h"

using namespace std;

Goomba::Goomba(const string& texture_file, double x_pos, double y_pos, const double &sprite_width, const double &sprite_height, const int &map_width, const int &map_height, const int &tile_width, const int &tile_height, const double &map_scale) {
  alive = true;
  x = sprite_width;
  y = sprite_height;
  m_texture.loadFromFile(texture_file);
  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(sprite_width * sprite_height * 4);

  m_vertices[0].position = sf::Vector2f(x_pos, y_pos);
  m_vertices[1].position = sf::Vector2f(x_pos + sprite_width, y_pos);
  m_vertices[2].position = sf::Vector2f(x_pos + sprite_width, y_pos + sprite_height);
  m_vertices[3].position = sf::Vector2f(x_pos, y_pos + sprite_height);

  m_vertices[0].texCoords = sf::Vector2f(0, 0);
  m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
  m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
  m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);

  right = true;
  x_vel = 0.1;
}

void Goomba::update(const double &delta_time, const int &map_rows, const int &map_columns, Player * player, vector<vector<int>> &level) {
  if (alive) {
    int y_midpoint = player->m_vertices[0].position.y + (player->sprite_height / 2);
    int x_midpoint = player->m_vertices[0].position.x + (player->sprite_width / 2);

    on_ground = (bool)level[(int)(m_vertices[3].position.y / 64)][(int)(m_vertices[3].position.x / 64)];

    player_left = player->m_vertices[0].position.x;
    player_right = player->m_vertices[2].position.x;
    player_up = player->m_vertices[0].position.y;
    player_down = player->m_vertices[2].position.y;
    enemy_left = m_vertices[0].position.x;
    enemy_right = m_vertices[2].position.x;
    enemy_up = m_vertices[0].position.y;
    enemy_down = m_vertices[2].position.y;

    if ((double)player_left / enemy_right < 1.01 && (double)player_right / enemy_left > 0.99 && (double)player_down / enemy_up > 0.99 && (double)player_up / enemy_down < 1.01) { 
      if ((double)player_left / enemy_right > 0.99 && ((player_up > enemy_up && player_up < enemy_down) || (player_down > enemy_up && player_down < enemy_down) || (y_midpoint > enemy_up && y_midpoint < enemy_down))) {
	player->m_vertices[0].position = sf::Vector2f(m_vertices[1].position.x + 25, player->m_vertices[0].position.y);
	player->m_vertices[1].position = sf::Vector2f(m_vertices[1].position.x + player->sprite_width + 25, player->m_vertices[1].position.y);
        player->m_vertices[2].position = sf::Vector2f(m_vertices[2].position.x + player->sprite_width + 25, player->m_vertices[2].position.y);
        player->m_vertices[3].position = sf::Vector2f(m_vertices[2].position.x + 25, player->m_vertices[3].position.y);
      } else if ((double)player_right / enemy_left < 1.01 && ((player_up > enemy_up && player_up < enemy_down) || (player_down > enemy_up && player_down < enemy_down) || (y_midpoint > enemy_up && y_midpoint < enemy_down))) {
	player->m_vertices[0].position = sf::Vector2f(m_vertices[0].position.x - player->sprite_width - 25, player->m_vertices[0].position.y);
        player->m_vertices[1].position = sf::Vector2f(m_vertices[0].position.x - 25, player->m_vertices[1].position.y);
        player->m_vertices[2].position = sf::Vector2f(m_vertices[3].position.x - 25, player->m_vertices[2].position.y);
        player->m_vertices[3].position = sf::Vector2f(m_vertices[3].position.x - player->sprite_width - 25, player->m_vertices[3].position.y);
      }
      if (((double)player_down / enemy_up > 0.99 && player_up < enemy_up) && ((player_left > enemy_left && player_left < enemy_right) || (player_right > enemy_left && player_right < enemy_right))) {
        alive = false;
        m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(0, 0);
	m_vertices[2].position = sf::Vector2f(0, 0);
	m_vertices[3].position = sf::Vector2f(0, 0);
      }
    }
    if (alive) {
      y_vel = 1;
      if (!on_ground) {
        m_vertices[0].position = sf::Vector2f(m_vertices[0].position.x, m_vertices[0].position.y + (y_vel * delta_time));
        m_vertices[1].position = sf::Vector2f(m_vertices[1].position.x, m_vertices[1].position.y + (y_vel * delta_time));
        m_vertices[2].position = sf::Vector2f(m_vertices[2].position.x, m_vertices[2].position.y + (y_vel * delta_time));
        m_vertices[3].position = sf::Vector2f(m_vertices[3].position.x, m_vertices[3].position.y + (y_vel * delta_time));
      }

      if (right && on_ground) {
        if (!level[(int)(m_vertices[2].position.y / 64) - 1][(int)(m_vertices[2].position.x / 64)] && level[(int)(m_vertices[2].position.y / 64)][(int)(m_vertices[2].position.x / 64)]) {
          x_vel = 0.1;
        } else {
          right = false;
         x_vel = 0;
        }
      }
      if (!right && on_ground) {
        if (level[(int)(m_vertices[3].position.y / 64)][(int)(m_vertices[3].position.x / 64) - 1] && !level[(int)(m_vertices[3].position.y / 64) - 1][(int)(m_vertices[3].position.x / 64)]) {
          x_vel = -.1;
        } else { 
          right = true;
        }
      }

        m_vertices[0].position = sf::Vector2f(m_vertices[0].position.x + (x_vel * delta_time), m_vertices[0].position.y);
        m_vertices[1].position = sf::Vector2f(m_vertices[1].position.x + (x_vel * delta_time), m_vertices[1].position.y);
        m_vertices[2].position = sf::Vector2f(m_vertices[2].position.x + (x_vel * delta_time), m_vertices[2].position.y);
        m_vertices[3].position = sf::Vector2f(m_vertices[3].position.x + (x_vel * delta_time), m_vertices[3].position.y);

    }
  }
}
