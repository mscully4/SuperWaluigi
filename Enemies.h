#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"

class Goomba : public Entity {
  private:
    int x_vel;
    int y_vel;
    int x;
    int y;
    bool left;
  public:
    Goomba(const std::string& texture_file, double x_pos, double y_pos, const double &sprite_width, const double &sprite_height, const int &map_width, const int &map_height, const int &tile_width, const int &tile_height, const double &map_scale);
    void update(double &delta_time, Player * player);
};
