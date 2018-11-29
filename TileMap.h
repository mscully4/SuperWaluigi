#pragma once

#include<vector>
#include<iostream>
#include "Tile.h"
#include "Entity.h"
#include <string>

using namespace std;

class TileMap : public sf::Transformable, public sf::Drawable {
	public:
		sf::Texture m_texture;
		sf::Transform m_transform;
		sf::VertexArray m_vertices;
		TileMap(const string& sprite_sheet, vector<vector<int>>&, const int tile_width, const int tile_height);
		const int tile_width = tile_width;
		const int tile_height = tile_height;
		vector<vector<int>> level;
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
