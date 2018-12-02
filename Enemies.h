#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"

class Goomba : public Entity {
  private:
    double x_vel;
    double y_vel;
    int x;
    int y;
    int player_left, player_right, player_up, player_down;
    int enemy_left, enemy_right, enemy_up, enemy_down;
    //update variables 
    bool on_ground;
    bool right;
    bool collision;
    bool alive;
  public:
    Goomba(const std::string& texture_file, double x_pos, double y_pos, const double &sprite_width, const double &sprite_height, const int &map_width, const int &map_height, const int &tile_width, const int &tile_height, const double &map_scale);
    void update(const double &delta_time, const int &map_rows, const int &map_columns, Player * player, vector<vector<int>> &level);
};
