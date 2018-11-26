#pragma once
#include<SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	public:
		sf::VertexArray m_vertices;
		sf::Texture m_texture;
		sf::Transform m_transform;
		Entity();
		~Entity();
};

class player : public Entity {

};
