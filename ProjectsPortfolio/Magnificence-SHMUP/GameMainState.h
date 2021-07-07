#pragma once
#include "State.h"
#include "Player.h"
#include "EntityRenderer.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>
#include <functional>
//Main State for this demo
class GameMainState : public State{
public: //std functions for bullets and enemies
	std::function<void(Bullet&)> moveStraight;

	std::function<void(Enemy& )> defaultSetup;
	std::function<void(Enemy&, float)> defaultUpdate;

public:
	GameMainState(Game& game, Resources res);
	~GameMainState();
	
	 bool handleEvent(sf::Event event) override;
	 bool update(sf::Time deltaTime) override;
	 void render(sf::RenderTarget& app) override;
private:
	 void createBullet(std::function<void(Bullet&)>& bulScript, std::vector<Bullet*>& vec, EntityRenderer& renderer, sf::Vector2f pos, float speed, float angle, BulletType graphic = BulletType::None, float delay = 0.f, float acceleration = 0.f, float angular = 0.f);
	 void setBulletGraphic(EntityRenderer& renderer, Bullet* bul, BulletType graphic);
	 void updatePlayerBullets(sf::Time deltatime);
	 void updateEnemyBullets(sf::Time deltatime);
	 void deleteBullets(std::vector<Bullet*>& vec, EntityRenderer& renderer, size_t index);
private:
	float mGlobalTime;
	sf::Text mDebugText;
	//player entity
	Player mPlayer;
	//entity containers 
	std::list<Enemy::EnemyData> mStageSpawn;
	std::vector<Enemy*> mEnemies;
	std::vector<Bullet*> mEnemyBullets;
	std::vector<Bullet*> mPlayerBullets;
	//entity renderers for bullets and pick-ups(maybe) 
	EntityRenderer mPlayerBulletRenderer;
	EntityRenderer mEnemyBulletRenderer;
};