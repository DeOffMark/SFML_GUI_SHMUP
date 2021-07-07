#include "Entity.h"


Entity::Entity(Game& game) : mIsAlive(true), mGame(&game), mCollider(0.f) {}

void Entity::update(sf::Time deltatime) {}

sf::Vector2f& Entity::getPosition() { return mPosition; }
sf::Vector2f& Entity::getDirection(){ return mDirection; }
float Entity::getAngle() { return mAngle; }
float Entity::getSpeed() { return mSpeed; }
void Entity::setPosition(sf::Vector2f pos) { mPosition = pos; }
void Entity::setAngle(float angle) { mAngle = angle; }

float& Entity::getCollider() {
	return mCollider;
}

void Entity::setupCollider(float radius) { mCollider = radius; }

bool Entity::isAlive() { return mIsAlive; }
void Entity::setAlive(bool b) { mIsAlive = b; }

bool Entity::isColliding(Entity& e ) {
	sf::Vector2f difference = mPosition - e.getPosition();
	return (e.getPosition().x - mPosition.x) * (e.getPosition().x - mPosition.x) + 
		(e.getPosition().y - mPosition.y) * (e.getPosition().y - mPosition.y) < 
		(mCollider + e.getCollider()) * (mCollider + e.getCollider());
}