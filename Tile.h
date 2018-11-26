#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Tile : public Entity {
	public:
		Tile(const std::string& textureFile, double x_pos, double y_pos, double tile_width, double tile_height, double texture_w, double texture_h);
		unsigned int m_obs_size[2];
		double m_half_size[2];
		double m_center_pos[2];
		double m_scale[2];
};
