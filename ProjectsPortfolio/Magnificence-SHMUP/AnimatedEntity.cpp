#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(Game& game) : Entity(game) {}

void AnimatedEntity::setup(sf::Texture& t, float x, float y, float angle, float speed) {
	mSprite.setTexture(t);
	mPosition.x = x; mPosition.y = y;
	mAngle = angle;
	mSpeed = speed;
}

void AnimatedEntity::setupAnimation(int x, int y, int w, int h, int count, float speed) {
	mAnim = Animation(x, y, w, h, count, speed);
	mSprite.setTextureRect(mAnim.getCurrentFrame());
	mSprite.setOrigin(float(mAnim.getCurrentFrame().width / 2), float(mAnim.getCurrentFrame().height / 2));
}

sf::Sprite& AnimatedEntity::getSprite() { return mSprite; }

 void AnimatedEntity::draw(sf::RenderTarget& app) {
	mSprite.setPosition(mPosition);
	mSprite.setRotation(mAngle);
	app.draw(mSprite);
}