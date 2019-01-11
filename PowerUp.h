#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Entity.h"
 
using namespace std;

class Player;
class PowerUp : public Entity {
  private:
    //int top_height;
    bool active;
    int x_tile, y_tile;  
    int x, y;
     
    //sound effects
    sf::SoundBuffer power_up_appear_buffer;
    sf::Sound power_up_appear;

  public:
    PowerUp(const std::string& texture_file, double x_pos, double y_pos, const double sprite_width, const double sprite_height, const int tile_width, const int tile_height, string type);
    void set_active(bool status);
    bool get_active();
    double get_x_tile();
    double get_y_tile();
};
