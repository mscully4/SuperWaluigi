#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "PowerUp.h"
#include "Chork.h"

using namespace std;

class Player : public Entity {
	double x_vel;
	double y_vel;
    bool right = true;
    bool alive = true;
    int big = 0;
    bool complete = false;
    int fire = 0;
    int invincible = 0;
    int oscillator = 0;
    sf::Clock oscillator_timer;
    int coins = 0;
    vector<vector<int>> key;
    vector<vector<int>> oscillating;
    vector<vector<PowerUp>> created_power_ups;
public:
	Player(const std::string textureFile, double x_pos, double y_pos, Chork& chork, vector<vector<PowerUp>>& created_power_ups);
	double sprite_width;
	double sprite_height;
	int chork_height, chork_width;
    bool is_chorking = false;
    sf::Clock chork_timer;	
    vector<vector<int>> chork_constants = {{ 30, -47, 15 }, { 45, -40, 10 }};
    void update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> &level, vector<PowerUp>& active_power_ups, Chork& chork);
	bool get_alive();
    void set_alive(bool status);
    bool get_big();
    void set_big(int status);
    int get_fire();
    void change_fire(int);
    int get_invincible();
    void change_invincible(int);
    bool get_complete();
    int get_coins();
    unsigned int m_obs_size[2];
	double m_half_size[2];
	double m_center_pos[2];
	//Update variables
	bool facing_right = true;
	bool key_left, key_up, key_down, key_right, key_c;

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

    sf::SoundBuffer grow_buffer;
    sf::Sound grow;

    sf::SoundBuffer coin_buffer;
    sf::Sound coin;

    sf::SoundBuffer yahoo_ee_buffer;
    sf::Sound yahoo_ee;
};
