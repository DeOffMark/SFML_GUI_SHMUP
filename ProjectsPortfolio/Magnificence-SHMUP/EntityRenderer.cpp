#include "EntityRenderer.h"



EntityRenderer::EntityRenderer(sf::Texture& texture) {
	mTexture = &texture;
}

void EntityRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = mTexture;
	target.draw(mVertices.data(), mVertices.size(), sf::Quads, states);
}