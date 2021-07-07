#pragma once
#include "AnimatedEntity.h"
#include <functional>
#include <array>

class Bullet;

enum class EnemyType {tSmall, tMedium1, tMedium2, tLarge, tMiniBoss, tBoss};

class Enemy : public AnimatedEntity {
public:
	struct EnemyData {
		EnemyData(float spawn, EnemyType type, std::function<void(Enemy&)>& setup, std::function<void(Enemy&, float)>& update, sf::Vector2f pos, float HP);
		float spawnTime;
		EnemyType mType;
		std::function<void(Enemy&)> setupScript;
		std::function<void(Enemy&, float)> updateScript;
		sf::Vector2f startingPosition;
		float hp;

	};
public:
	std::array<float, 5> mScriptValues;
	Enemy(Game& game, EnemyData& data);
	float getGlobalTime();
	void update(sf::Time deltatime) override;
private:
	float mGlobalTime;
	EnemyData mData;
};