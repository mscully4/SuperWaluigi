#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Entity.h"
 
using namespace std;

class Chork : public Entity {
    private:
        //int top_height;
        bool active;
        int x, y;
        int sprite_width, sprite_height;
        //sound effects
        sf::SoundBuffer chorking_buffer;
        sf::Sound chorking;
    public:
        Chork(const string& texture_file, double x_pos, double y_pos, const double& sprite_width, const double& sprite_height);
        int get_sprite_width();
        int get_sprite_height();
};
