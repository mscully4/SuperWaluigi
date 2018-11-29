#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Enemies.h"
#include "Player.h"

using namespace std;

Goomba::Goomba(const string& texture_file, double x_pos, double y_pos, const double &sprite_width, const double &sprite_height, const int &map_width, const int &map_height, const int &tile_width, const int &tile_height, const double &map_scale) {
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
}

void Goomba::update(double &delta_time, Player * player) {
  /*if (m_vertices[0].position.x + (x_vel * delta_time) >= 0 && m_vertices[2].position.x + (x_vel * delta_time) <= map_width * tile_width * map_scale) {
    for (int i = 0; i < 4; ++i) {
      m_vertices[i].position.x += x_vel * delta_time;
    }
  }*/
  if (player->m_vertices[0].position.y < m_vertices[1].position.y && player->m_vertices[0].position.y > m_vertices[2].position.y) {
    cout << "HIT" << endl;
  }
}
