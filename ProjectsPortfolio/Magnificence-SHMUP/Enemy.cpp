#include "Enemy.h"

Enemy::EnemyData::EnemyData(float spawn, EnemyType type, std::function<void(Enemy&)>& setup, std::function<void(Enemy&, float)>& update, sf::Vector2f pos, float HP) :
spawnTime(spawn), mType(type), setupScript(setup), updateScript(update), startingPosition(pos), hp(HP)
{}

Enemy::Enemy(Game& game, EnemyData& data) : AnimatedEntity(game), mData(data), mGlobalTime(0.f){
	setupCollider(15.f);
	mScriptValues = { 0.f, 0.f, 0.f, 0.f, 0.f };
	data.setupScript(*this);

}

float Enemy::getGlobalTime() { return mGlobalTime; }

void Enemy::update(sf::Time deltatime){
	mData.updateScript(*this, deltatime.asSeconds());
	mGlobalTime += deltatime.asSeconds();
}