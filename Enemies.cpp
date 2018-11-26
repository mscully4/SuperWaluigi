#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Enemies.h"

using namespace std;

Goomba::Goomba(const string& texture_file, double x_pos, double y_pos, double sprite_width, double sprite_height) {
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
