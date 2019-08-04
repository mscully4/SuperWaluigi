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
    bool show;
    int tile_width, tile_height;
    int x, y;
    string type; 
    //sound effects
    sf::SoundBuffer power_up_appear_buffer;
    sf::Sound power_up_appear;

  public:
    PowerUp(const std::string& texture_file, const int tile_width, const int tile_height, string type);
    void set_show(bool status);
    void set_coordinates(const int&, const int&);
    bool get_show();
    string get_type();
    int get_x();
    int get_y();
    sf::Clock timer;
    bool completed = false;
};
