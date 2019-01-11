#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Entity.h"
#include "PowerUp.h"
using namespace std;

PowerUp::PowerUp(const string& texture_file, double x_tile, double y_tile, const double sprite_width, const double sprite_height, const int tile_width, const int tile_height, string type) {
    this->x_tile = x_tile;
    this->y_tile = y_tile;
  
    x = x_tile * tile_width;
    y = (y_tile - 1) * tile_height;
  
    bool active = true;
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

    power_up_appear_buffer.loadFromFile("Assets/sounds/power_up_appears.wav");
    power_up_appear.setBuffer(power_up_appear_buffer);
    power_up_appear.play();
};

double PowerUp::get_x_tile() {
    return this->x_tile;
}

double PowerUp::get_y_tile() {
    return this->y_tile;
}

void PowerUp::set_active(bool status) {
    this->active = status;
}

bool PowerUp::get_active() {
    return this->active;
}
