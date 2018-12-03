#pragma once

#include<vector>
#include<iostream>
#include "Entity.h"

using namespace std;

class Ending : public sf::Transformable, public  sf::Drawable {
  public:
    sf::Texture m_texture;
    sf::Texture m_transform;
    sf::VertexArray m_vertices;
    Ending(const string& texture, const int &width, const int &height, const int &map_width, const int &map_height);
  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
