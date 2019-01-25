#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Entity.h"
 
using namespace std;

class PowerUp : public Entity {
  private:
    //int top_height;
    bool active;
    int x_tile, y_tile;  
    int x, y;
    string type; 
    //sound effects
    sf::SoundBuffer power_up_appear_buffer;
    sf::Sound power_up_appear;

  public:
    PowerUp(const std::string& texture_file, int x_pos, int y_pos, const double sprite_width, const double sprite_height, const int tile_width, const int tile_height, string type);
    void set_active(bool status);
    double get_x_tile();
    double get_y_tile();
    bool get_active();
    string get_type();
    sf::Clock timer;
    bool completed = false;
};
