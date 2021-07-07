#pragma once
#include <SFML/Graphics.hpp>

class Game;

class Entity { // entity that will be used for 
public:
	Entity(Game& game);

	virtual void update(sf::Time);

	sf::Vector2f& getPosition();
	sf::Vector2f& getDirection();
	float getSpeed();
	void setPosition(sf::Vector2f pos);
	void setAngle(float angle);
	float getAngle();
	bool isAlive();
	void setAlive(bool b);

	float& getCollider();

	void setupCollider(float radius = 0.f);

	bool isColliding( Entity& e);

protected:
	Game* mGame; // pointer to the scene the entity's state is at to access stuff like window height and width
	float mCollider; // Radial collider used for this game for now...
	bool mIsAlive;
	sf::Vector2f mPosition;
	sf::Vector2f mDirection;
	float mSpeed;
	float mAngle;
};