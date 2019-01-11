#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "PowerUp.h"

using namespace std;

class PowerUp;
class Player : public Entity {
	double x_vel;
	double y_vel;
    bool alive = true;
    bool big = false;
public:
	Player(const std::string textureFile, double x_pos, double y_pos, double image_width, double image_height);
	double sprite_width;
	double sprite_height;
	void update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> &level, vector<PowerUp>& PowerUps);
	bool get_alive();
    void set_alive(bool status);
    bool get_big();
    void set_big(bool status);
    unsigned int m_obs_size[2];
	double m_half_size[2];
	double m_center_pos[2];
	
	//Update variables
	bool facing_right;
	bool key_left, key_up, key_down, key_right;

	//soundtrack
	sf::SoundBuffer wah_buffer;
    sf::Sound wah;

	sf::SoundBuffer oh_ho_buffer;
	sf::Sound oh_ho;

	sf::SoundBuffer winner_buffer;
	sf::Sound winner;

	sf::SoundBuffer ow_buffer;
	sf::Sound ow;

    sf::SoundBuffer break_block_buffer;
	sf::Sound break_block;
    
    sf::SoundBuffer break_mystery_buffer;
	sf::Sound break_mystery;
};
