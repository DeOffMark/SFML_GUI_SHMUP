#include "Player.h"
#include "Utilities.hpp"
#include "Game.h"

Player::Player(Game& game) : AnimatedEntity(game), isShooting(false), isFocused(false), isInvincible(false), isDashing(false){
    setupCollider(2.f);
    setupAnimation(0, 0, 32, 32, 3, 0.5f);
	mTimer = 0.f;
    mDashTimer = 0.f;
}

float Player::getTimer() { return mTimer; }
float Player::getDashTimer() { return mDashTimer; }

void Player::setTimer(float timer) { mTimer = timer; }

void Player::update(sf::Time deltatime) {
 
	mAnim.update();
    mSprite.setTextureRect(mAnim.getCurrentFrame());
	sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 1.f;
    }
 
    if (length2(movement) > 1.f) {
        movement = normalize(movement);
    }

    if (isFocused) {
        mSpeed = 150.f;
    }
    else {
        mSpeed = 300.f;
    }

    mPosition += movement * mSpeed * deltatime.asSeconds();
    //clamp the player's position inside the screen boundaries
    mPosition.x = clamp(mPosition.x, float(mSprite.getTextureRect().width / 2), float(mGame->getWindowWidth() - mSprite.getTextureRect().width / 2));
    mPosition.y = clamp(mPosition.y, float(mSprite.getTextureRect().height / 2), float(mGame->getWindowHeight() - mSprite.getTextureRect().height / 2));
    
    mTimer -= deltatime.asSeconds();
   
}