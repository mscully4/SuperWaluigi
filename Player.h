#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Player : public Entity {
private:
	double x_vel;
	double y_vel;
	double sprite_height;
	double sprite_width;
public:
	Player(const std::string& textureFile, double x_pos, double y_pos, double image_width, double iamge_height);
	void update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale);
	unsigned int m_obs_size[2];
	double m_half_size[2];
	double m_center_pos[2];
	double m_scale[2];
	bool m_collide;
	bool m_on_ground;
	bool facing_right;
	bool key_left, key_up, key_down, key_right;
};
