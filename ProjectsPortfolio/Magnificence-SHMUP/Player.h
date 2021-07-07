#pragma once
#include "AnimatedEntity.h"
//entity that we take control in gaming states
class Player : public AnimatedEntity {
public:
	Player(Game& game);

	void update(sf::Time deltatime) override;

	float getTimer();
	float getDashTimer();
	void setTimer(float timer);

	bool isShooting, isFocused, isInvincible;
	bool isDashing;
protected:
	
	float mTimer, mDashTimer;
};