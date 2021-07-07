#include "Bullet.h"
#include "Game.h"
#include "Utilities.hpp"


Bullet::Bullet(Game& game, sf::Vector2f position, sf::Vector2f direction, float speed, float angle, BulletType graphic, float delay) : Entity(game), mAcceleration(0.f), mAngularMomentum(0.f), mGlobalTime(0.f) {
	mPosition = position;
	mDirection = direction;
	mSpeed = speed;
	mAngle = angle;
	mGraphic = graphic;
	mDelay = delay;
	mScriptValues = { 0.f, 0.f, 0.f, 0.f, 0.f };
}

float Bullet::getAcceleration() { return mAcceleration; }
void Bullet::setAcceleration(float acc) { mAcceleration = acc; }
void Bullet::setAngularMomentum(float ang) { mAngularMomentum = ang; }
float Bullet::getAngularMomentum() { return mAngularMomentum; }
float Bullet::getGlobablTime() { return mGlobalTime; }

void Bullet::setupScript(std::function<void(Bullet& b)> script) {
	mUpdateScript = script;
}

void Bullet::update(sf::Time deltatime) {
	if (mDelay > 0.f) {
		mDelay -= deltatime.asSeconds();
	}
	else {
		mUpdateScript(*this);
		mAngle += mAngularMomentum;
		mSpeed = mSpeed + mAcceleration;
		mPosition += mDirection * (mSpeed);
		
		if (mPosition.x > mGame->getWindowWidth() + 20.f || mPosition.x < -20.f || mPosition.y > mGame->getWindowHeight() + 20.f|| mPosition.y < -20.f) mIsAlive = false;
	}
	mGlobalTime += deltatime.asSeconds();
}