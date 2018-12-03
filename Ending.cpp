#include<SFML/Graphics.hpp>
#include "Ending.h"
#include<iostream>
#include<vector>

using namespace std;

Ending::Ending(const string& sprite_sheet, const int &ending_width, const int &ending_height, const int &map_width, const int &map_height) {
  m_texture.loadFromFile(sprite_sheet);
  m_vertices.setPrimitiveType(sf::Quads);
  int rows = 9;
  int cols = 2;
  m_vertices.resize(rows * cols * 4);
  sf::Vector2u tile_size(64, 64);
  for (int i = 0; i < cols; ++i) {
    for (int j = 0; j < rows; ++j) {
      sf::Vertex* quad = &m_vertices[(i + j * cols) * 4];
      
      quad[0].position = sf::Vector2f(map_width + (j * tile_size.x), (map_height - 128) + i * tile_size.y);
      quad[1].position = sf::Vector2f(map_width + ((j + 1) * tile_size.x), (map_height - 128) + i * tile_size.y);
      quad[2].position = sf::Vector2f(map_width + ((j + 1) * tile_size.x), (map_height - 128) + ((i + 1) * tile_size.y));
      quad[3].position = sf::Vector2f(map_width + (j * tile_size.x), (map_height - 128) + ((i + 1) * tile_size.y));

      quad[0].texCoords = sf::Vector2f(0, 0);
      quad[1].texCoords = sf::Vector2f(32, 0);
      quad[2].texCoords = sf::Vector2f(32, 32);
      quad[3].texCoords = sf::Vector2f(0, 32);

    }
  }
  sf::Vertex* flag = &m_vertices[64];
  flag[0].position = sf::Vector2f(map_width, 100);
  flag[1].position = sf::Vector2f(map_width + 80, 100);
  flag[2].position = sf::Vector2f(map_width + 80, (map_height - 128));
  flag[3].position = sf::Vector2f(map_width, (map_height - 128));

  flag[0].texCoords = sf::Vector2f(253, 11);
  flag[1].texCoords = sf::Vector2f(290, 11);
  flag[2].texCoords = sf::Vector2f(290, 206);
  flag[3].texCoords = sf::Vector2f(253, 206);

  sf::Vertex* castle = &m_vertices[68];
  castle[0].position = sf::Vector2f(map_width + 150, 200);
  castle[1].position = sf::Vector2f(map_width + 500, 200);
  castle[2].position = sf::Vector2f(map_width + 500, (map_height - 128));
  castle[3].position = sf::Vector2f(map_width + 150, (map_height - 128));

  castle[0].texCoords = sf::Vector2f(0, 66);
  castle[1].texCoords = sf::Vector2f(193, 66);
  castle[2].texCoords = sf::Vector2f(193, 206);
  castle[3].texCoords = sf::Vector2f(0, 206);
};

void Ending::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  states.texture = &m_texture;
  target.draw(m_vertices, states);
} 
