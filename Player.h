#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"

using namespace std;

class Player : public Entity {
	double x_vel;
	double y_vel;
public:
	Player(const std::string& textureFile, double x_pos, double y_pos, double image_width, double iamge_height);
	double sprite_width;
	double sprite_height;
	void update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> &level);
	unsigned int m_obs_size[2];
	double m_half_size[2];
	double m_center_pos[2];
	int lives = 3;
	
	//Update variables
	bool facing_right;
	bool key_left, key_up, key_down, key_right;
};

