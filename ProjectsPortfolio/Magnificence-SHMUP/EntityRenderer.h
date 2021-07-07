#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


//such renderers as this are designed to draw multiple entities at once, optimizing code to reduce amount of draw functions()
class EntityRenderer : public sf::Drawable, public sf::Transformable {
public:

	EntityRenderer(sf::Texture& texture);
	

	sf::Texture* mTexture;
	std::vector<sf::Vertex> mVertices;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};