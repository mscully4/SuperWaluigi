#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Goomba : public Entity {
  private:
    int x_vel;
    int y_vel;
  public:
    Goomba(const std::string& texture_file, double x_pos, double y_pos, double width, double height);
};
