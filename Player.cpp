#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Entity.h"
#include "Player.h"
#include <stdio.h>

using namespace std; 

Player::Player(const std::string textureFile, double x_pos, double y_pos, Chork& chork, vector<vector<PowerUp>>& power_ups)
 {
    this->sprite_width = 58;
    this->sprite_height = 106;

    m_texture.loadFromFile(textureFile);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(sprite_width * sprite_height * 4);

	m_vertices[0].position = sf::Vector2f(x_pos, y_pos);
	m_vertices[1].position = sf::Vector2f(x_pos + sprite_width, y_pos);
	m_vertices[2].position = sf::Vector2f(x_pos + sprite_width, y_pos + sprite_height);
	m_vertices[3].position = sf::Vector2f(x_pos, y_pos + sprite_height);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
	m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
	m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);

    this->created_power_ups = power_ups;

    wah_buffer.loadFromFile("Assets/sounds/wah.wav");
    wah.setBuffer(wah_buffer);
	wah.setVolume(20.f);

	oh_ho_buffer.loadFromFile("Assets/sounds/oh-ho.wav");
    oh_ho.setBuffer(oh_ho_buffer);

	winner_buffer.loadFromFile("Assets/sounds/winner.wav");
	winner.setBuffer(winner_buffer);

    ow_buffer.loadFromFile("Assets/sounds/ow.wav");
    ow.setBuffer(ow_buffer);

    break_block_buffer.loadFromFile("Assets/sounds/break_block.wav");
    break_block.setBuffer(break_block_buffer);

    break_mystery_buffer.loadFromFile("Assets/sounds/break_mystery.wav");	
    break_mystery.setBuffer(break_mystery_buffer);

    grow_buffer.loadFromFile("Assets/sounds/grow.wav");
    grow.setBuffer(grow_buffer);

    coin_buffer.loadFromFile("Assets/sounds/Coin.wav");
    coin.setBuffer(coin_buffer);

    yahoo_ee_buffer.loadFromFile("Assets/sounds/yahoo-ee.wav");
    yahoo_ee.setBuffer(yahoo_ee_buffer);

    x_vel = 0.0f;
	y_vel = 0.0f;
    
    this->chork_width = chork.get_sprite_width();
    this->chork_height = chork.get_sprite_height();

    srand(time(NULL));
}

bool Player::get_alive() {
    return this->alive;
}

void Player::set_alive(bool status) {
    this->alive = status;
}

bool Player::get_big() {
    return this->big;
}

void Player::set_big(int status) {
    this->big = status;
}

int Player::get_fire() {
    return this->fire;
}

void Player::change_fire(int change) {
    this->fire += change;
}

int Player::get_invincible() {
    return this->invincible;
}

void Player::change_invincible(int change) {
    this->invincible += change;
}

bool Player::get_complete() {
    return this->complete;
}

int Player::get_coins() {
    return this->coins;
}

void Player::update(double delta_time, const int map_rows, const int map_columns, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> &level, vector<PowerUp>& active_power_ups, Chork& chork) {
    key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    key_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    key_c = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    
    static bool isFalling = true;
    static bool isJumping = false;
    static bool beginJump = true;
    static bool isDescending = true;
    static bool cont = true;
    const int height = m_vertices[2].position.y;
    static int ground = (map_columns - 1) * tile_height  * map_scale;
    const int maxHeight = ground - ((map_scale*tile_height) * 4.5);
    const int minHeight = ground - ((map_scale*tile_height) * 2);
    const double speedScale = 0.75;

    double x_pos;
  
    this->sprite_width = (big ? 74 : 58);
    this->sprite_height = (big ? 125 : 106); 
    

    m_vertices[0].position = sf::Vector2f(m_vertices[0].position.x, m_vertices[0].position.y);
	m_vertices[1].position = sf::Vector2f(m_vertices[0].position.x + sprite_width, m_vertices[0].position.y);
	m_vertices[2].position = sf::Vector2f(m_vertices[0].position.x + sprite_width, m_vertices[0].position.y + sprite_height);
	m_vertices[3].position = sf::Vector2f(m_vertices[0].position.x, m_vertices[0].position.y + sprite_height);
    
    if (invincible) {
        if (oscillator) {
            x_pos = (big ? 199 : 137);
        } else {
            x_pos = (big ? 62 : 0);
        }
    } else {
        x_pos = (big ? 62 : 0);
    }
 
    //if the left key is pressed, adjust velocity to 1 * speedScale
    if (key_left) {
	    x_vel = -1 * speedScale;
        facing_right = false;
    }

    //if the right key is pressed, adjust velocity to 1 * speedScale
    if (key_right) {
	    x_vel = 1 * speedScale;
        facing_right = true;
    }
    
    //if no keys are pressed, do nothing
    if (!key_left && !key_right) {
	    x_vel = 0;
    }

    //make the sprite face right 
    if (facing_right) {
        m_vertices[0].texCoords = sf::Vector2f(x_pos, 0);
        m_vertices[1].texCoords = sf::Vector2f(x_pos + sprite_width, 0);
        m_vertices[2].texCoords = sf::Vector2f(x_pos + sprite_width, sprite_height);
        m_vertices[3].texCoords = sf::Vector2f(x_pos, sprite_height);
    //make the sprite face left
    } else {
        m_vertices[0].texCoords = sf::Vector2f(x_pos + sprite_width, 0);
        m_vertices[1].texCoords = sf::Vector2f(x_pos, 0);
        m_vertices[2].texCoords = sf::Vector2f(x_pos, 0 + sprite_height);
        m_vertices[3].texCoords = sf::Vector2f(x_pos + sprite_width, 0 + sprite_height);
    }
    //the sprite is on the descent of a jump
    if (isJumping && !key_up) {
        isFalling = true;
    }
    
       
    //jumps can only be initiated when the player is on the ground    
    if (key_up && !isFalling && !isDescending && height <= minHeight) {
	    beginJump = true;
    //if the player hasn't reached the max jump height then keep going up
	if (height >= maxHeight) {
	    y_vel = -1 * speedScale;
	    isJumping = true;
	} 
	
    //else go back down
    else {
        isFalling = true;
	}}
    
	
    //if the player has initiated a jump and hasn't reached the minimum jump height, then keep going up
    if (beginJump && height > minHeight && !isDescending){
	wah.play();
	    y_vel = -1 * speedScale;
	    isJumping = true;
    }
	
    if (key_up) {
	    beginJump = true;
    }
	
    if (!key_up){
        isJumping = false;
    }


    //if the player is on their way down
    if (isFalling) {
	//this makes sure the player reaches a certain height before they can begin descending
        if(height <= minHeight) {
       	    y_vel = speedScale;
	        isDescending = true;
	    }
    }

    //if the player hasn't reached the end
    if(cont) {
	    //moving left
	    if (x_vel < 0) {
	        //if the tile directly to the left of the bottom left point, upper left point or the midpoint between the two isn't air
	        if (level[((m_vertices[3].position.y - 2) / (map_scale * tile_width))][(m_vertices[3].position.x + (x_vel * delta_time))/ (map_scale * tile_width)] != 0 ||
	        level[(m_vertices[0].position.y) / (map_scale * tile_width)][(m_vertices[0].position.x + (x_vel * delta_time)) / (map_scale * tile_width)] != 0 || 
            level[(m_vertices[0].position.y + m_vertices[3].position.y) / (2 * map_scale * tile_width)][(m_vertices[0].position.x + (x_vel * delta_time)) / (map_scale * tile_width)] != 0)  {
                x_vel = 0;
	        }
	    } 
        //moving right
        else if (x_vel > 0) {
	        //if the tile to the right of the bottom right point, upper right point or the midpoint between the two isn't air
	        if (level[((m_vertices[2].position.y - 2) / (map_scale * tile_width))][(m_vertices[2].position.x + (x_vel * delta_time)) / (map_scale * tile_width)] != 0 ||
	        level[m_vertices[1].position.y / (map_scale * tile_width)][(m_vertices[1].position.x + (x_vel * delta_time)) / (map_scale * tile_width)] != 0 || 
            level[(m_vertices[1].position.y + m_vertices[2].position.y) / (2 * map_scale * tile_width)][(m_vertices[1].position.x + (x_vel * delta_time)) / (map_scale * tile_width)] != 0)  {
                x_vel = 0;
	    }
	}


	//if the player is within the bounds of the map, move according to the x velocity
	if (m_vertices[0].position.x + (x_vel * delta_time) >= 0) {
		for (int i = 0; i < 4; ++i) {
			m_vertices[i].position.x += x_vel * delta_time;
		}
	} 

    if (y_vel != 0) {
        //if the player is moving down
		if (y_vel > 0) {
            //the seg fault is caused by the line underneath, most likely something to do with level
            if (level[(m_vertices[3].position.y + (y_vel * delta_time)) / tile_width][m_vertices[3].position.x / tile_width] == 0 
            && level[(m_vertices[2].position.y + (y_vel * delta_time)) / tile_width][m_vertices[2].position.x / tile_width] == 0 
            && level[(m_vertices[2].position.y + (y_vel * delta_time)) / tile_width][(m_vertices[2].position.x + m_vertices[3].position.x) / (2 * tile_width)] == 0) {
			//if the tile to the bottom left, bottom right and beneath the midpoint between the two is air
                //then move the player down
				for (int i = 0; i < 4; ++i) {
                    m_vertices[i].position.y += y_vel * delta_time;
				}

	        //if the player falls off the map
            if (m_vertices[2].position.y >= (map_columns * tile_width) - 1) {
                cout << "FELL OFF MAP " << m_vertices[2].position.y << endl;
	            ow.play();
	            this->alive = false;
                m_vertices[0].position = sf::Vector2f(0, 0);
                m_vertices[1].position = sf::Vector2f(sprite_width, 0);
                m_vertices[2].position = sf::Vector2f(sprite_width, sprite_height);
                m_vertices[3].position = sf::Vector2f(0, sprite_height);
            }

		}
			//if not,
			else {
				//the player must be on the ground
				ground = m_vertices[2].position.y;
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				isDescending = false;
			}
        //the player is moving up
		} else if (y_vel < 0) {
			//if the move would keep the player within the bounds of the map, and the tiles above the top left and top right points of the player are air
            if (m_vertices[0].position.y + (y_vel * delta_time) >= 0 && 
			level[(m_vertices[0].position.y + (y_vel * delta_time)) / tile_width][m_vertices[0].position.x / tile_width] == 0 &&
            level[(m_vertices[0].position.y + (y_vel * delta_time)) / tile_width][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)] == 0 &&
			level[(m_vertices[1].position.y + (y_vel * delta_time)) / tile_width][m_vertices[1].position.x / tile_width] == 0) {
		        //move the player
				for (int i = 0; i < 4; ++i) {
					m_vertices[i].position.y += (y_vel * delta_time);
				}
			} else {
                //dont let the player jump
				ground = m_vertices[2].position.y;
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				
				isDescending = false;
			    
                int top_left = level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[0].position.x / tile_width];
	            int top_center = level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)];
                int top_right = level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[1].position.x / tile_width];
                cout << "Mushrooms: " << created_power_ups[0].size() << " Chorks: " << created_power_ups[1].size() << " Stars: " << created_power_ups[2].size() << endl;

                //if the top left corner of the player hits a breakable box,
                if (top_left == 2) {
                    //then replace the block with air
                    level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[0].position.x / tile_width] = 0;
                    break_block.play();
                } else if (top_left == 3) {
                    this->coins += 1;
                    //randomly determine whether to turn the mystery block into a broken block
                    if ((double)rand() / RAND_MAX > .8) {
                        //replace the block with a broken mystery block
                        level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + (x_vel * delta_time)) / tile_width] = 5;
                        break_mystery.play();
                    } else {
                        coin.play();
                    }
                } else if (top_left == 10) {
                    //make a powerup appear
                    active_power_ups.push_back(created_power_ups[0].back());
                    created_power_ups[0].pop_back();
                    active_power_ups.back().set_coordinates(m_vertices[0].position.x, m_vertices[0].position.y);
                    active_power_ups.back().set_show(true);
                    //then replace the block with a broken mystery block
                    level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[0].position.x / tile_width] = 5;
                    break_mystery.play();
                } else if (top_left == 11) {
                    //make a powerup appear
                    active_power_ups.push_back(created_power_ups[1].back());
                    created_power_ups[1].pop_back();
                    active_power_ups.back().set_coordinates(m_vertices[0].position.x, m_vertices[0].position.y);
                    active_power_ups.back().set_show(true);
                    //then replace the block with a broken mystery block
                    level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[0].position.x / tile_width] = 5;
                    break_mystery.play();
                }  else if (top_left == 12) {
                    //make a powerup appear
                    active_power_ups.push_back(created_power_ups[2].back());
                    created_power_ups[2].pop_back();
                    active_power_ups.back().set_coordinates(m_vertices[0].position.x, m_vertices[0].position.y);
                    active_power_ups.back().set_show(true);
                    //then replace the block with a broken mystery block
                    level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[0].position.x / tile_width] = 5;
                    break_mystery.play();
                }
                
                //this is to avoid double dipping
                if ((int)(m_vertices[0].position.x / tile_width) != (int)(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)) {
                    //if the top midpoint of the player hits a breakable box
                    if (top_center == 2) {
                        //then replace the block with air
                        level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)] = 0;
                        break_block.play();
                    } else if (top_center == 3) {
                        this->coins += 1;
                        //randomly determine whether to turn the mystery block into a broken block
                        if ((double)rand() / RAND_MAX > .8) {
                            //replace the block with a broken mystery block
                            level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)] = 5;				
                            break_mystery.play();
                        } else {
                            coin.play();
                        }
                    } else if (top_center == 10) {
                        //make a powerup appear
                        active_power_ups.push_back(created_power_ups[0].back());
                        created_power_ups[0].pop_back();
                        active_power_ups.back().set_coordinates((m_vertices[0].position.x + m_vertices[1].position.x)  / 2, (m_vertices[0].position.y + m_vertices[1].position.y)  / 2);
                        active_power_ups.back().set_show(true);
                        //then replace the block with a broken mystery block
                        level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)] = 5;
                        break_mystery.play();
                    } else if (top_center == 11) {
                        //make a powerup appear
                        active_power_ups.push_back(created_power_ups[1].back());
                        created_power_ups[1].pop_back();
                        active_power_ups.back().set_coordinates((m_vertices[0].position.x + m_vertices[1].position.x)  / 2, (m_vertices[0].position.y + m_vertices[1].position.y)  / 2);
                        active_power_ups.back().set_show(true);
                        //then replace the block with a broken mystery block
                        level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)] = 5;				
                        break_mystery.play();
                    } else if (top_center == 12) {
                        //make a powerup appear
                        active_power_ups.push_back(created_power_ups[2].back());
                        created_power_ups[2].pop_back();
                        active_power_ups.back().set_coordinates((m_vertices[0].position.x + m_vertices[1].position.x)  / 2, (m_vertices[0].position.y + m_vertices[1].position.y)  / 2);
                        active_power_ups.back().set_show(true);
                        //then replace the block with a broken mystery block
                        level[((m_vertices[0].position.y + (y_vel * delta_time)) / tile_width) - 1][(m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width)] = 5;				
                        break_mystery.play();
                    }
                }

                if ((int)(m_vertices[1].position.x / tile_width) != (int)(m_vertices[0].position.x / tile_width) && 
                (int)(m_vertices[1].position.x / tile_width) != (int)((m_vertices[0].position.x + m_vertices[1].position.x) / (2 * tile_width))) {
                    //if the top right corner of the player hits a breakable box,
                    if (top_right == 2) {
                        //then replace the block with air
                        level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[1].position.x / tile_width] = 0;
                        break_block.play();
                    } else if (top_right == 3) {
                        this->coins += 1;
                        //randomly determine whether to turn the mystery block into a broken block
                        if ((double)rand() / RAND_MAX > .8) {
                            //replace the block with a broken mystery block
                            level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[1].position.x / tile_width] = 5;				
                            break_mystery.play();
                        } else {
                            coin.play();
                        }
                    } else if (top_right == 10) {
                        active_power_ups.push_back(created_power_ups[0].back());
                        created_power_ups[0].pop_back();
                        active_power_ups.back().set_coordinates(m_vertices[1].position.x, m_vertices[1].position.y);
                        active_power_ups.back().set_show(true);
                            //then replace the block with a broken mystery block
                        level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[1].position.x / tile_width] = 5;
                        //the player should also stop moving upwards
                        break_mystery.play();
                    } else if (top_right == 11) {
                        active_power_ups.push_back(created_power_ups[1].back());
                        created_power_ups[1].pop_back();
                        active_power_ups.back().set_coordinates(m_vertices[1].position.x, m_vertices[1].position.y);
                        active_power_ups.back().set_show(true);
                            //then replace the block with a broken mystery block
                        level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[1].position.x / tile_width] = 5;
                        break_mystery.play();
                    } else if (top_right == 12) {
                        active_power_ups.push_back(created_power_ups[2].back());
                        created_power_ups[2].pop_back();
                        active_power_ups.back().set_coordinates(m_vertices[1].position.x, m_vertices[1].position.y);
                        active_power_ups.back().set_show(true);
                        //then replace the block with a broken mystery block
                        level[((m_vertices[1].position.y + (y_vel * delta_time)) / tile_width) - 1][m_vertices[1].position.x / tile_width] = 5;
                        break_mystery.play();
                    }
                
                }
		    }
	    }
    }
    //if the player's y_vel == 0
	else {
        //so long as the tile beneath the bottom left and bottom right corners of the player are air
        if (level[(m_vertices[2].position.y + (y_vel * speedScale * delta_time)) / (map_scale * tile_width)][m_vertices[3].position.x / (map_scale * tile_width)] == 0 && 
        level[(m_vertices[2].position.y + (y_vel * speedScale * delta_time)) / (map_scale * tile_width)][m_vertices[2].position.x / (map_scale * tile_width)] == 0 &&
        level[(m_vertices[2].position.y + 1 + (y_vel * speedScale * delta_time)) / (map_scale * tile_width)][(m_vertices[2].position.x + m_vertices[3].position.x) / (2 * map_scale * tile_width)] == 0) {
            isFalling = true;
            isDescending = true;
            y_vel = 1 * speedScale;
            //move the player down
            for (int i = 0; i < 4; ++i) {
                m_vertices[i].position.y += y_vel * delta_time;
            }
        }
	}
        //iterate through out list of power-ups
        for (int i=0; i < active_power_ups.size(); ++i) {
            //check if the player has collected a power up
            int power_up_row = active_power_ups[i].get_x() / tile_width;
            int power_up_column = active_power_ups[i].get_y() / tile_height;

            //map position of the top left corner of the player
            int top_left_column = (m_vertices[0].position.y + (y_vel * delta_time)) / (map_scale * tile_width);
            int top_left_row = (m_vertices[0].position.x + (x_vel * delta_time)) / (map_scale * tile_width);

            //map position of the top right corner of the player
            int top_right_column = (m_vertices[1].position.y + (y_vel * delta_time)) / (map_scale * tile_width);
            int top_right_row = (m_vertices[1].position.x + (x_vel * delta_time)) / (map_scale * tile_width);

            //map position of the bottom left corner of the player
            int bottom_left_column = (m_vertices[3].position.y + (y_vel * delta_time)) / (map_scale * tile_width);
            int bottom_left_row = (m_vertices[3].position.x + (x_vel * delta_time))/ (map_scale * tile_width);

            //map position of the bottom right corner of the player
            int bottom_right_column = (m_vertices[2].position.y + (y_vel * delta_time)) / (map_scale * tile_width);
            int bottom_right_row = (m_vertices[2].position.x + (x_vel * delta_time)) / (map_scale * tile_width);

            //printf("PowerUp: %i, %i  TL: %i, %i  TR: %i, %i  BL %i, %i  BR: %i, %i \n", power_up_row, power_up_column, top_left_row, top_left_column, top_right_row, top_right_column, bottom_left_row, bottom_left_column, bottom_right_row, bottom_right_column);
            if ((top_left_row == power_up_row && (top_left_column + 2) == power_up_column) ||
            (top_right_row == power_up_row && (top_right_column + 2) == power_up_column) || 
            (bottom_left_row == power_up_row && bottom_left_column == power_up_column) || 
            (bottom_right_row == power_up_row && bottom_right_column  == power_up_column)) {
                if (active_power_ups[i].get_type() == "Mushroom" && active_power_ups[i].get_show()) {
                    if (big == false) {
                        this->set_big(1);
                        grow.play();
                    }
                } else if (active_power_ups[i].get_type() == "Chork" && active_power_ups[i].get_show()) {
                    active_power_ups[i].timer.restart();
                    this->change_fire(1);
                    active_power_ups[i].completed = true;
                } else if (active_power_ups[i].get_type() == "Star" && active_power_ups[i].get_show()) {
                    active_power_ups[i].timer.restart();
                    this->change_invincible(1);
                    active_power_ups[i].completed = true;
                }
               active_power_ups[i].set_show(false);
            }
     //check if active power-ups have expired
            if (active_power_ups[i].get_type() == "Star") {
                double elapsed = active_power_ups[i].timer.getElapsedTime().asSeconds();
                if (elapsed > 20 && active_power_ups[i].completed) {
                    this->change_invincible(-1);
                    active_power_ups[i].completed = false;
                }
            }
            if (active_power_ups[i].get_type() == "Chork") {
                double elapsed = active_power_ups[i].timer.getElapsedTime().asSeconds();
                if (elapsed > 20 && active_power_ups[i].completed) {
                    this->change_fire(-1);
                    active_power_ups[i].completed = false;
                }
            }
        }

        //this checks if the player is currently invicible and if so cycles the player sprite
        if (invincible) {
            if (oscillator_timer.getElapsedTime().asSeconds() > 1) {
                oscillator = -oscillator + 1;
                oscillator_timer.restart();
            }
        }

        static bool can_chork = true;
        if (fire) {
            if (!can_chork) {
                if (chork_timer.getElapsedTime().asSeconds() > 3) {
                    cout << 1 << endl;
                    can_chork = true;
                }
            } else if (key_c && !is_chorking && can_chork) {
                cout << 2 << endl;
                is_chorking = true;
                chork_timer.restart();
                chork.chorking.play();
            } else if (!key_c && is_chorking && chork_timer.getElapsedTime().asSeconds() > 3) {
                cout << 3 << endl;
                is_chorking = false;
                can_chork = false;
            } else if (is_chorking) {
                if (chork_timer.getElapsedTime().asSeconds() > 4) {
                    cout << 4 << endl;
                    is_chorking = false;
                    can_chork = false;
                    chork_timer.restart();
                }
            }
        }
        if (is_chorking) {
            if (facing_right) {
                //update the chork to face right
                chork.m_vertices[0].texCoords = sf::Vector2f(0, 0);
                chork.m_vertices[1].texCoords = sf::Vector2f(chork_width, 0);
                chork.m_vertices[2].texCoords = sf::Vector2f(chork_width, chork_height);
                chork.m_vertices[3].texCoords = sf::Vector2f(0, chork_height);
             } else {
                //update the chork to face left
                chork.m_vertices[0].texCoords = sf::Vector2f(chork_width, 0);
                chork.m_vertices[1].texCoords = sf::Vector2f(0, 0);
                chork.m_vertices[2].texCoords = sf::Vector2f(0, chork_height);
                chork.m_vertices[3].texCoords = sf::Vector2f(chork_width, chork_height);
            }

            if (this->get_big() == 1) {
                chork.m_vertices[0].position = sf::Vector2f(m_vertices[0].position.x + (facing_right ? 42 : -40), m_vertices[0].position.y + 10);
            } else {
                chork.m_vertices[0].position = sf::Vector2f(m_vertices[0].position.x + (facing_right ? 33 : -47), m_vertices[0].position.y + 15);
            }
            //move the chork with the player
            double chork_x_pos = chork.m_vertices[0].position.x, chork_y_pos = chork.m_vertices[0].position.y;
            chork.m_vertices[1].position = sf::Vector2f(chork_x_pos + chork_width, chork_y_pos);
            chork.m_vertices[2].position = sf::Vector2f(chork_x_pos + chork_width, chork_y_pos + chork_height);
            chork.m_vertices[3].position = sf::Vector2f(chork_x_pos, chork_y_pos + chork_height);
        } else {
            chork.m_vertices[0].position = sf::Vector2f(0, 0);
            chork.m_vertices[1].position = sf::Vector2f(0, 0);
            chork.m_vertices[2].position = sf::Vector2f(0, 0);
            chork.m_vertices[3].position = sf::Vector2f(0, 0);
        }



        //this checks if the player has won and triggers the ending animation	
	    if ((m_vertices[2].position.x + (x_vel * delta_time)) / (map_scale * tile_width) >= (float)map_rows - .1) {
	        winner.play();
	        x_vel = 0;
	        y_vel = 0;
	        cont = false;
        }
    //the game is over and it is time for the ending sequence
   } else {
        chork.m_vertices[0].position = sf::Vector2f(0, 0);
        chork.m_vertices[1].position = sf::Vector2f(0, 0);
        chork.m_vertices[2].position = sf::Vector2f(0, 0);
        chork.m_vertices[3].position = sf::Vector2f(0, 0);
        //if the player is on the ground
        if ((int)m_vertices[2].position.y == (map_columns - 2) * tile_height) { 
            //move him into he enters the castle
            if (m_vertices[2].position.x < (map_rows * tile_width) + 350) {
                for (int i=0; i<4; ++i) {
                    m_vertices[i].position.x = m_vertices[i].position.x + 0.25;
                }
            //then kill the program
            } else {
                this->complete = true;
            }
        //if the player is in the air
        } else {
            //move him to the ground before doing anything
            for (int i=0; i<4; ++i) {
                m_vertices[i].position.y +=1;
            }
        }
    }
}
