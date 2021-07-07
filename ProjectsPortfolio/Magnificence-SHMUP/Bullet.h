#pragma once
#include "Entity.h"
#include <functional>
#include <array>
enum class BulletType{ None = 0, PlayerMain, PlayerHoming, PlayerSpread, sBulletRed, sBulletOrange, sBulletYellow, sBulletGreen, sBulletCyan, sBulletBlue, sBulletPurple, sBulletGray, 
    mBulletRed, mBulletOrange, mBulletYellow, mBulletGreen, mBulletCyan, mBulletBlue, mBulletPurple, mBulletGray,
    rBulletRed, rBulletOrange, rBulletYellow, rBulletGreen, rBulletCyan, rBulletBlue, rBulletPurple, rBulletGray,
    lBulletRed, lBulletOrange, lBulletYellow, lBulletGreen, lBulletCyan, lBulletBlue, lBulletPurple, lBulletGray,
    aBulletRed, aBulletOrange, aBulletYellow, aBulletGreen, aBulletCyan, aBulletBlue, aBulletPurple, aBulletGray,
    laserRed, laserOrange, laserYellow, laserGreen, laserCyan, laserBlue, laserPurple, laserGray, laserRainbow};

class Bullet :public Entity{
public:
	Bullet(Game& game, sf::Vector2f position, sf::Vector2f direction, float speed, float angle, BulletType graphic, float delay);

	float getAcceleration();
	void setAcceleration(float acc);
	void setAngularMomentum(float ang);
	float getAngularMomentum();
	float getGlobablTime();
	void setupScript(std::function<void(Bullet& b)> script);


	void update(sf::Time deltatime) override;

	std::array<float, 5> mScriptValues;
protected:
	float mGlobalTime;
	float mDelay; 
	BulletType mGraphic;
	float mAcceleration;
	float mAngularMomentum;
	std::function<void(Bullet& b)> mUpdateScript;
};