#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Player.h"

using namespace std; 

Player::Player(const std::string& textureFile, double x_pos, double y_pos, double image_width, double image_height) {
	sprite_width = image_width;
	sprite_height = image_height;

	m_texture.loadFromFile(textureFile);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(image_width * image_height * 4);

	m_vertices[0].position = sf::Vector2f(x_pos, y_pos);
	m_vertices[1].position = sf::Vector2f(x_pos + image_width, y_pos);
	m_vertices[2].position = sf::Vector2f(x_pos + image_width, y_pos + sprite_height);
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

	x_vel = 0.0f;
	y_vel = 0.0f;

}

void Player::update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> &level) {
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
    const int height = m_vertices[2].position.y + (y_vel * delta_time);
    static int ground = (map_height - 1) * tile_height  * map_scale;
    const int maxHeight = ground - ((2*tile_height) * 4.5);
    const int minHeight = ground - ((2*tile_height) * 2);
    const double speedScale = 0.75;
    if(isJumping && !key_up){
        isFalling = true;
    }
    
	if (key_left) {
		x_vel = -1 * speedScale;
		m_vertices[0].texCoords = sf::Vector2f(sprite_width, 0);
	    m_vertices[1].texCoords = sf::Vector2f(0, 0);
		m_vertices[2].texCoords = sf::Vector2f(0, sprite_height);
		m_vertices[3].texCoords = sf::Vector2f(sprite_width, sprite_height);
	}
	if (key_up && !isFalling && height <= minHeight && !isDescending) {
	    beginJump = true;
	    if(height >= maxHeight){
		    y_vel = -1 * speedScale;
		    isJumping = true;
		}
		else{
		    isFalling = true;
		}
	}
	if(beginJump && height > minHeight && !isDescending){
	    y_vel = -1 * speedScale;
	    isJumping = true;
	}
	
	if (key_up){
	    beginJump = true;
	}
	
	if (!key_up){
	    isJumping = false;
	}
	if (isFalling) {
	    if(height <= minHeight && beginJump){
	        y_vel = 1 * speedScale;
	        isDescending = true;
	        
		}
	}
	
	if (key_right) {
		x_vel = 1 * speedScale;
	    m_vertices[0].texCoords = sf::Vector2f(0, 0);
		m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
		m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
		m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);
	}

	if (!key_left && !key_right) {
		x_vel = 0;
	}
	if(cont){
	if (x_vel < 0){
	    if(level[m_vertices[2].position.y/(2*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[m_vertices[0].position.y/(2*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[(m_vertices[0].position.y + m_vertices[2].position.y)/(4*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ){
            x_vel = 0;
	    }
	}
	else if (x_vel > 0){
	    if(level[m_vertices[2].position.y/(2*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[m_vertices[0].position.y/(2*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[(m_vertices[0].position.y + m_vertices[2].position.y)/(4*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ){
            x_vel = 0;
	    }
	}
	else if (level[m_vertices[3].position.y/(2*tile_width)][m_vertices[3].position.x/(2*tile_width)] != 0 || 
	level[m_vertices[2].position.y/(2*tile_width)][m_vertices[2].position.x/(2*tile_width)] != 0){
	    x_vel = 0;
	}
	if (m_vertices[0].position.x + (x_vel * delta_time) >= 0 &&
	m_vertices[2].position.x + (x_vel * delta_time) <= map_width * tile_width * map_scale) {
		for (int i = 0; i < 4; ++i) {
			m_vertices[i].position.x += x_vel * delta_time;
		}
	}
	
	if (y_vel != 0){
	    if (y_vel > 0){
    	    if (level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
    	    level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
    	    level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + m_vertices[1].position.x)/(4*tile_width)] == 0) {
    		    for (int i = 0; i < 4; ++i) {
    			    m_vertices[i].position.y += y_vel * delta_time;
    		    }
    	    }
	        else{
	            ground = m_vertices[2].position.y;
	            y_vel = 0;
	            isFalling = false;
	            beginJump = false;
	            minHeightReached = false;
	            isDescending = false;
	        }
	    }
	    else {
	        if (m_vertices[0].position.y + (y_vel * delta_time) >= 0 && 
    	    level[((m_vertices[0].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
    	    level[((m_vertices[0].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0) {
    		    for (int i = 0; i < 4; ++i) {
    			    m_vertices[i].position.y += y_vel * delta_time;
    		    }
    	    }
	        else{
	            ground = m_vertices[2].position.y;
	            y_vel = 0;
	            isFalling = false;
	            beginJump = false;
	            minHeightReached = false;
	            isDescending = false;
	        }
	        if (level[((m_vertices[0].position.y - (speedScale * delta_time))/(2*tile_width))][(m_vertices[0].position.x)/(2*tile_width)] == 2){
	            level[((m_vertices[0].position.y - (speedScale * delta_time) - 5)/(2*tile_width))][(m_vertices[0].position.x)/(2*tile_width)] = 0;
	            y_vel = 0;
	            isFalling = false;
	            beginJump = false;
	            minHeightReached = false;
	            isDescending = false;
	        }
	        else if (level[((m_vertices[0].position.y - (speedScale * delta_time))/(2*tile_width))][(m_vertices[1].position.x)/(2*tile_width)] == 2){
	            level[((m_vertices[0].position.y - (speedScale * delta_time) - 5)/(2*tile_width))][(m_vertices[1].position.x)/(2*tile_width)] = 0;
	            y_vel = 0;
	            isFalling = false;
	            beginJump = false;
	            minHeightReached = false;
	            isDescending = false;
	        }
	    }
	    
	}
	else {
          if (level[((m_vertices[3].position.y + delta_time)/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
          level[((m_vertices[3].position.y + delta_time)/(2*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0) {
              isFalling = true;
              isDescending = true;
              y_vel = 1 * speedScale;
              for (int i = 0; i < 4; ++i) {
                          m_vertices[i].position.y += y_vel * delta_time;
              }
          }
          else {
    	    
          }
	}
	}
	
	if(m_vertices[1].position.x/(2*tile_width) >= (float)map_width - .03){
	    for (int i = 0; i < 4; ++i){
	        m_vertices[i] = m_vertices[0];
	        m_vertices[i].position.x += .03;
	    }
	    
	    x_vel = 0;
	    y_vel = 0;
	    cont = false;
	}
	
	
    m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
    m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];
    if(m_vertices[3].position.y + 2 * y_vel * delta_time >= map_height * 2 * tile_width){
        Player::lives -= 1;
        m_vertices[0].position = sf::Vector2f(0, 0);
		m_vertices[1].position = sf::Vector2f(sprite_width, 0);
		m_vertices[2].position = sf::Vector2f(sprite_width, sprite_height);
		m_vertices[3].position = sf::Vector2f(0, sprite_height);
    }
}


/*void Player::update(double delta_time, const int map_width, const int map_height, const int tile_width, const int tile_height, const int map_scale, vector<vector<int>> level) {
	key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	key_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	
    static bool isFalling = true;
    static bool isJumping = false;
    static bool beginJump = true;
    static bool minHeightReached = true;
    static bool isDescending = true;
    const int height = m_vertices[2].position.y + (y_vel * delta_time);
    static int ground = (map_height - 1) * tile_height  * map_scale;
    const int maxHeight = ground - ((2*tile_height) * 4.5);
    const int minHeight = ground - ((2*tile_height) * 2);
    const double speedScale = 0.75;
    
    if(isJumping && !key_up){
        isFalling = true;
    }
    
	if (key_left) {
		x_vel = -1 * speedScale;
		m_vertices[0].texCoords = sf::Vector2f(sprite_width, 0);
	    m_vertices[1].texCoords = sf::Vector2f(0, 0);
		m_vertices[2].texCoords = sf::Vector2f(0, sprite_height);
		m_vertices[3].texCoords = sf::Vector2f(sprite_width, sprite_height);
	}
	if (key_up && !isFalling && height <= minHeight && !isDescending) {
	    beginJump = true;
	    if(height >= maxHeight){
		    y_vel = -1 * speedScale;
		    isJumping = true;
		}
		else{
		    isFalling = true;
		}
	}
	if(beginJump && height > minHeight && !isDescending){
	    y_vel = -1 * speedScale;
	    isJumping = true;
	}
	
	if (key_up){
	    beginJump = true;
	}
	
	if (!key_up){
	    isJumping = false;
	}
	if (isFalling) {
	    if(height <= minHeight && beginJump){
	        y_vel = 1 * speedScale;
	        isDescending = true;
	        
		}
	}
	
	if (key_right) {
		x_vel = 1 * speedScale;
	    m_vertices[0].texCoords = sf::Vector2f(0, 0);
		m_vertices[1].texCoords = sf::Vector2f(sprite_width, 0);
		m_vertices[2].texCoords = sf::Vector2f(sprite_width, sprite_height);
		m_vertices[3].texCoords = sf::Vector2f(0, sprite_height);
	}

	if (!key_left && !key_right) {
		x_vel = 0;
	}
	if (x_vel < 0){
	    if(level[m_vertices[2].position.y/(2*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[m_vertices[0].position.y/(2*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[(m_vertices[0].position.y + m_vertices[2].position.y)/(4*tile_width)][(m_vertices[3].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ){
            x_vel = 0;
	    }
	}
	else if (x_vel > 0){
	    if(level[m_vertices[2].position.y/(2*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[m_vertices[0].position.y/(2*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ||
	    level[(m_vertices[0].position.y + m_vertices[2].position.y)/(4*tile_width)][(m_vertices[2].position.x + (x_vel * delta_time))/(2*tile_width)] != 0 ){
            x_vel = 0;
	    }
	}
	else if (level[m_vertices[3].position.y/(2*tile_width)][m_vertices[3].position.x/(2*tile_width)] != 0 || 
	level[m_vertices[2].position.y/(2*tile_width)][m_vertices[2].position.x/(2*tile_width)] != 0){
	    x_vel = 0;
	}
	if (m_vertices[0].position.x + (x_vel * delta_time) >= 0 &&
	m_vertices[2].position.x + (x_vel * delta_time) <= map_width * tile_width * map_scale) {
		for (int i = 0; i < 4; ++i) {
			m_vertices[i].position.x += x_vel * delta_time;
		}
	}
	if (y_vel != 0){
	    if (y_vel > 0){
    	    if (level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
    	    level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
    	    level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + m_vertices[1].position.x)/(4*tile_width)] == 0) {
    		    for (int i = 0; i < 4; ++i) {
    			    m_vertices[i].position.y += y_vel * delta_time;
    		    }
    	    }
	        else{
	            ground = m_vertices[2].position.y;
	            y_vel = 0;
	            isFalling = false;
	            beginJump = false;
	            minHeightReached = false;
	            isDescending = false;
	        }
	    }
	    else {
	        if (m_vertices[0].position.y + (y_vel * delta_time) >= 0 && 
    	    level[((m_vertices[0].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
    	    level[((m_vertices[0].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0) {
    		    for (int i = 0; i < 4; ++i) {
    			    m_vertices[i].position.y += y_vel * delta_time;
    		    }
    	    }
	        else{
	            ground = m_vertices[2].position.y;
	            y_vel = 0;
	            isFalling = false;
	            beginJump = false;
	            minHeightReached = false;
	            isDescending = false;
	        }
	    }
	    
	}
	else {
          if (level[((m_vertices[3].position.y + delta_time)/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)] == 0 &&
          level[((m_vertices[3].position.y + delta_time)/(2*tile_width))][(m_vertices[1].position.x + (x_vel * delta_time))/(2*tile_width)] == 0) {
              isFalling = true;
              isDescending = true;
              y_vel = 1 * speedScale;
              for (int i = 0; i < 4; ++i) {
                          m_vertices[i].position.y += y_vel * delta_time;
                  }
          }
          else {
    	    
          }
	}
	
    
    std::cout << level[((m_vertices[3].position.y + (y_vel * delta_time))/(2*tile_width))][(m_vertices[0].position.x + (x_vel * delta_time))/(2*tile_width)];
    std::cout << y_vel << std::endl;
    m_center_pos[0] = m_vertices[0].position.x + m_half_size[0];
    m_center_pos[1] = m_vertices[0].position.y + m_half_size[1];
}*/
