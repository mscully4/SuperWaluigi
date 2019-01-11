#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"

using namespace std; 

Player::Player(const std::string textureFile, double x_pos, double y_pos, double image_width, double image_height)
 {
    sprite_width = image_width;
	sprite_height = image_height;
    
    m_texture.loadFromFile(textureFile);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(image_width * image_height * 4);

	m_vertices[0].position = sf::Vector2f(x_pos, y_pos);
	m_vertices[1].position = sf::Vector2f(x_pos + image_width, y_pos);
	m_vertices[2].position = sf::Vector2f(x_pos + image_width, y_pos + image_height);
	m_vertices[3].position = sf::Vector2f(x_pos, y_pos + image_height);

	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(image_width, 0);
	m_vertices[2].texCoords = sf::Vector2f(image_width, image_height);
	m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);

	m_obs_size[0] = m_vertices[1].position.x - m_vertices[0].position.x;
	m_obs_size[1] = m_vertices[3].position.y - m_vertices[0].position.y;
	m_half_size[0] = m_obs_size[0] / 2;
	m_half_size[1] = m_obs_size[1] / 2;
	m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
	m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];

	//std::cout << m_obs_size[0] << ", " << m_obs_size[1] << std::endl;
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
    x_vel = 0.0f;
	y_vel = 0.0f;

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

void Player::set_big(bool status) {
    this->big = status;
}

void Player::update(double delta_time, const int map_rows, const int map_columns, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> &level, vector<PowerUp>& power_ups) {
    key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    key_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	
    static bool isFalling = true;
    static bool isJumping = false;
    static bool beginJump = true;
    static bool minHeightReached = true;
    static bool isDescending = true;
    static bool cont = true;
    const int height = m_vertices[2].position.y;
    static int ground = (map_columns - 1) * tile_height  * map_scale;
    const int maxHeight = ground - ((map_scale*tile_height) * 4.5);
    const int minHeight = ground - ((map_scale*tile_height) * 2);
    const double speedScale = 0.75;
           
    //map position of the top left corner of the player
    int top_left_column = ((m_vertices[0].position.y - (speedScale * delta_time))/(map_scale*tile_width));
    int top_left_row =  (m_vertices[0].position.x)/(map_scale*tile_width);

    //map position of the top right corner of the player
    int top_right_column = ((m_vertices[1].position.y - (speedScale * delta_time))/(map_scale*tile_width));
    int top_right_row = (m_vertices[1].position.x)/(map_scale*tile_width);

    //map position of the top left corner of the player
    int bottom_left_column = ((m_vertices[3].position.y - (speedScale * delta_time))/(map_scale * tile_width));
    int bottom_left_row =  (m_vertices[3].position.x) / (map_scale * tile_width);

    //map position of the top right corner of the player
    int bottom_right_column = ((m_vertices[2].position.y - (speedScale * delta_time)) / (map_scale * tile_width));
    int bottom_right_row = (m_vertices[2].position.x) / (map_scale * tile_width);

    
    //the sprite is on the descent of a jump
    if (isJumping && !key_up) {
        isFalling = true;
    }
    
    if (key_left) {
	x_vel = -1 * speedScale;
	//make the sprite face left      
	m_vertices[0].texCoords = sf::Vector2f(sprite_width, 0);
	m_vertices[1].texCoords = sf::Vector2f(0, 0);
	m_vertices[2].texCoords = sf::Vector2f(0, sprite_height);
	m_vertices[3].texCoords = sf::Vector2f(sprite_width, sprite_height);
    }
    
    //jumps can only be initiated when the player is on the ground    
    if (key_up && !isFalling && !isDescending && height <= minHeight) {
	beginJump = true;
	//if the player hasn't reached the max jump height then keep going up
	if (height >= maxHeight) {
	    y_vel = -1 * speedScale;
	    isJumping = true;
	} else {
	//else go back down
            isFalling = true;
	}
    }
	
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
       	    y_vel = 1 * speedScale;
	    isDescending = true;
	}
    }
	
    if (key_right) {
	x_vel = 1 * speedScale;
	//make the sprite face right
	m_vertices[0].texCoords = sf::Vector2f(0, 0);
	m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
	m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
	m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);
    }

    //if no keys are pressed, do nothing
    if (!key_left && !key_right) {
	x_vel = 0;
    }

    //if the player hasn't reached the end
    if(cont) {
	//moving left
	if (x_vel < 0) {
	    //if the tile directly to the left of the bottom left point, upper left point or the midpoint between the two isn't air
	    if (level[m_vertices[3].position.y/(map_scale*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(map_scale*tile_width)] != 0 ||
	 level[(m_vertices[0].position.y + m_vertices[2].position.y)/(4*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 || 
	 level[m_vertices[0].position.y/(map_scale*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(map_scale*tile_width)] != 0) {
                x_vel = 0;
	    }
	}
	//moving right
	else if (x_vel > 0) {
	    //if the tile to the right of the bottom right point, upper right point or the midpoint between the two isn't air
	    if(level[m_vertices[2].position.y/(2*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[m_vertices[0].position.y/(2*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[(m_vertices[0].position.y + m_vertices[2].position.y)/(4*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ) {
                x_vel = 0;
	    }
	}
	//Not sure what this does	
	/*else if (level[m_vertices[3].position.y/(map_scale*tile_width)][m_vertices[3].position.x/(map_scale*tile_width)] != 0 || 
	level[m_vertices[2].position.y/(map_scale*tile_width)][m_vertices[2].position.x/(map_scale*tile_width)] != 0){
	    x_vel = 0;
	}*/

	//if the player is within the bounds of the map, move according to the x velocity
	if (m_vertices[0].position.x + (x_vel * delta_time) >= 0 &&
	m_vertices[2].position.x + (x_vel * delta_time) <= map_rows * tile_width * map_scale) {
		for (int i = 0; i < 4; ++i) {
			m_vertices[i].position.x += x_vel * delta_time;
		}
	}
	
	if (y_vel != 0) {
		//if the player is moving down
		if (y_vel > 0) {
			//if the tile to the bottom left, bottom right and beneath the midpoint between the two is air
			if (level[((m_vertices[3].position.y + (y_vel * delta_time))/(map_scale*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
					level[((m_vertices[3].position.y + (y_vel * delta_time))/(map_scale*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
					level[((m_vertices[3].position.y + (y_vel * delta_time))/(map_scale*tile_width))][(m_vertices[0].position.x + m_vertices[1].position.x)/(2*(map_scale*tile_width))] == 0) {
				//then move the player down
				for (int i = 0; i < 4; ++i) {
					m_vertices[i].position.y += y_vel * delta_time;
				}
			}
			//if not,
			else {
				//the player must be on the ground
				ground = m_vertices[2].position.y;
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				minHeightReached = false;
				isDescending = false;
			}
		}
		//if the player is moving up
		else {
			//if the move would keep the player within the bounds of the map, and the tiles above the top left and top right points of the player are air
			if (m_vertices[0].position.y + (y_vel * delta_time) >= 0 && 
					level[((m_vertices[0].position.y + (y_vel * delta_time))/(map_scale*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(map_scale*tile_width)] == 0 &&
					level[((m_vertices[0].position.y + (y_vel * delta_time))/(map_scale*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(map_scale*tile_width)] == 0) {
				//move the player
				for (int i = 0; i < 4; ++i) {
					m_vertices[i].position.y += y_vel * delta_time;
				}
			}
			//if not, then don't let the player jump	
			else {
				ground = m_vertices[2].position.y;
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				minHeightReached = false;
				isDescending = false;
			}

            
			//if the top left corner of the player hits a breakable box,
			if (level[top_left_column][top_left_row] == 2) {
				//then replace the block with air
				level[top_left_column][top_left_row] = 0;
				//the player should also stop moving upward
                break_block.play();
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				minHeightReached = false;
				isDescending = false;
			}
			//if the top right corner of the player hits a breakable box,
			else if (level[top_right_column][top_right_row] == 2) {
				//then replace the block with air
				level[top_right_column][top_right_row] = 0;
                break_block.play();
				//the player should also stop moving upwards
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				minHeightReached = false;
				isDescending = false;
			}

			//if the top left corner of the player hits a mystery block
			if (level[top_left_column][top_left_row] == 3){
                //make a powerup appear
               // PowerUp power_up("Assets/images/Goomba.png", top_left_column, top_right_column, 32, 32, 32, 32, "Chork");
                power_ups.push_back(PowerUp("Assets/images/Mushroom.png", top_left_row, top_left_column, 64, 64, 64, 64, "Chork"));
				//then replace the block with a broken mystery block
                level[top_left_column][top_left_row] = 5;				
				//the player should also stop moving upwards
				break_mystery.play();
                y_vel = 0;
				isFalling = false;
				beginJump = false;
				minHeightReached = false;
				isDescending = false;
			}
			//if the top right corner of the player hits a mystery block
			else if (level[top_right_column][top_right_row] == 3) {
                power_ups.push_back(PowerUp("Assets/images/Mushroom.png", top_right_row, top_right_column, 64, 64, 64, 64, "Chork"));
				//then replace the block with a broken mystery block
				level[top_right_column][top_right_row] = 5;
				//the player should also stop moving upwards
				break_mystery.play();
				y_vel = 0;
				isFalling = false;
				beginJump = false;
				minHeightReached = false;
				isDescending = false;
			}
		}
	}
    //if the player's y_vel == 0
	else {
        //so long as the tile beneath the bottom left and bottom right corners of the player are air
        if (level[bottom_left_column + 1][bottom_left_row] == 0 && level[bottom_right_column + 1][bottom_right_row] == 0) {
            isFalling = true;
            isDescending = true;
            y_vel = 1 * speedScale;
            //move the player down
            for (int i = 0; i < 4; ++i) {
                m_vertices[i].position.y += y_vel * delta_time;
            }
        }
	}

        //if the player hits a power up
        for (int i=0; i < power_ups.size(); ++i) {
            int power_up_row = power_ups[i].get_x_tile();
            int power_up_column = power_ups[i].get_y_tile();
            
            if((top_left_row == power_up_row && top_left_column + 2 == power_up_column) ||
            (top_right_row == power_up_row && top_right_column + 2 == power_up_column) || 
            (bottom_left_row == power_up_row && bottom_left_column + 1 == power_up_column) || 
            (bottom_right_row == power_up_row && bottom_right_column + 1 == power_up_column)) {
                if (power_ups[i].get_active()) {
                    this->big = true;
                }
                power_ups[i].set_active(false);
            }
        }
        
        //this triggers the ending animation	
	    if (bottom_right_row >= (float)map_rows - .03) {
	        winner.play();
	        for (int i = 0; i < 4; ++i) {
	            m_vertices[i] = m_vertices[0];
	            m_vertices[i].position.x += .03;
	        }
	            x_vel = 0;
	            y_vel = 0;
	            cont = false;
	    }
	
        m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
        m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];
        
    //if the player falls off the map
        if(m_vertices[3].position.y + 2 * y_vel * delta_time >= map_columns * 2 * tile_width){
	        ow.play();
	        this->alive = false;
            m_vertices[0].position = sf::Vector2f(0, 0);
            m_vertices[1].position = sf::Vector2f(sprite_width, 0);
            m_vertices[2].position = sf::Vector2f(sprite_width, sprite_height);
            m_vertices[3].position = sf::Vector2f(0, sprite_height);
        }
    }
}
