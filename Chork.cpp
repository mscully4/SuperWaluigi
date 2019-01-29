#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Entity.h"
#include "Chork.h"

using namespace std;

Chork::Chork(const string& texture_file, double x_pos, double y_pos, const double& sprite_width, const double& sprite_height) {
    this->x = x_pos;
    this->y = y_pos;
    this->active = true;
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    
    m_texture.loadFromFile(texture_file);
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(sprite_width * sprite_height * 4);

    m_vertices[0].position = sf::Vector2f(x, y);
    m_vertices[1].position = sf::Vector2f(x + sprite_width, y);
    m_vertices[2].position = sf::Vector2f(x + sprite_width, y + sprite_height);
    m_vertices[3].position = sf::Vector2f(x, y + sprite_height);

    m_vertices[0].texCoords = sf::Vector2f(0, 0);
    m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
    m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
    m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);

    chorking_buffer.loadFromFile("Assets/sounds/chork.wav");
    chorking.setBuffer(chorking_buffer);
};

int Chork::get_sprite_width() {
    return this->sprite_width;
}

int Chork::get_sprite_height() {
    return this->sprite_height;
}
