#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Entity.h"
#include "PowerUp.h"
using namespace std;

PowerUp::PowerUp(const string& texture_file, const int tile_width, const int tile_height, string type) {
    this->tile_width = tile_width;
    this->tile_height = tile_height;
    this->type = type;  
    this->show = false;

  
    m_texture.loadFromFile(texture_file);
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(tile_width * tile_height * 4);
    
    
    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(0, 0);
    m_vertices[2].position = sf::Vector2f(0, 0);
    m_vertices[3].position = sf::Vector2f(0, 0);

    m_vertices[0].texCoords = sf::Vector2f(0, 0);
    m_vertices[1].texCoords = sf::Vector2f(tile_width, 0);
    m_vertices[2].texCoords = sf::Vector2f(tile_width, tile_height);
    m_vertices[3].texCoords = sf::Vector2f(0, tile_height);
    

    power_up_appear_buffer.loadFromFile("Assets/sounds/power_up_appears.wav");
    power_up_appear.setBuffer(power_up_appear_buffer);
    power_up_appear.play(); 
};

void PowerUp::set_coordinates(const int& x_pos, const int& y_pos) {
    this->x = floor(x_pos / tile_width) * tile_width;
    this->y = (floor(y_pos / tile_width) - 2) * tile_height;
    m_vertices[0].position = sf::Vector2f(x, y);
    m_vertices[1].position = sf::Vector2f(x + tile_width, y);
    m_vertices[2].position = sf::Vector2f(x + tile_width, y + tile_height);
    m_vertices[3].position = sf::Vector2f(x, y + tile_height);
}

int PowerUp::get_x() {
    return this->x;
}

int PowerUp::get_y() {
    return this->y;
}

void PowerUp::set_show(bool status) {
    this->show = status;
}

bool PowerUp::get_show() {
    return this->show;
}

string PowerUp::get_type() {
    return this->type;
}
