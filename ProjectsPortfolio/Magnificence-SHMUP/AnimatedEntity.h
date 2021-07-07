#pragma once
#include "Entity.h"
#include "Animation.h"

class AnimatedEntity : public Entity {
public:
	AnimatedEntity(Game& game); 

	void setup(sf::Texture& t, float x = 0.f, float y = 0.f, float angle = 0.f, float speed = 0.f); 

	void setupAnimation(int x, int y, int w, int h, int count = 1, float speed = 0.f);

	sf::Sprite& getSprite();

	virtual void draw(sf::RenderTarget& app);
	
protected:
	Animation mAnim;
	sf::Sprite mSprite;
};