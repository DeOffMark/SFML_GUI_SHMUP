#include "GameMainState.h"
#include "Game.h"
#include "Utilities.hpp"
GameMainState::GameMainState(Game& game, Resources res) : State(game, res), mPlayer(game), mPlayerBulletRenderer(res.textures->get("tPlayer")), 
		mEnemyBulletRenderer(res.textures->get("tEnemyBullets")), mGlobalTime(0.f) {
	mPlayer.setup(res.textures->get("tPlayer"), game.getWindowWidth() / 2.f, game.getWindowHeight() / 2.f, 0.f, 300.f);
	mDebugText.setFont(res.fonts->get("tDebug")); 
	mDebugText.setCharacterSize(10);
	mDebugText.setPosition(10.f, 50.f);

	//setup entities' scripts
	moveStraight = [&](Bullet& b) {
		if (b.getPosition().x <= 0.f + b.getCollider() || b.getPosition().x >= getPointerToGame()->getWindowWidth() - b.getCollider()){
			b.getDirection().x = -b.getDirection().x;
			//b.setAngle(acosf(b.getDirection().x));
		}
	};

	defaultSetup = [&](Enemy& e) {
		e.setup(getResources().textures->get("tEnemy"), getPointerToGame()->getWindowWidth() / 2.f, 100.f, 0.f, 0.f);
		e.setupAnimation(0, 0, 360, 450);
		e.getSprite().scale(0.1f, 0.1f);
	};

	defaultUpdate = [&](Enemy& e, float deltatime) {
		if (e.getGlobalTime() >= 1.f) {
			float timer1s = 1.5f;
			if (e.mScriptValues[0] <= 0.f) {
				float angleT = float(rand() % 360);	
				for (int i = 0; i < 50; ++i) {
					createBullet(moveStraight, mEnemyBullets, mEnemyBulletRenderer, e.getPosition(), 420.f * deltatime, angleT, BulletType::mBulletRed, 0.f, 0.01f);
					
					angleT += 360.f / 50.f;
				}
				e.mScriptValues[0] = timer1s;
			}
			e.mScriptValues[0] -= deltatime;
		}
	};

	mStageSpawn.push_back(Enemy::EnemyData(0.f, EnemyType::tBoss, defaultSetup, defaultUpdate, sf::Vector2f(game.getWindowWidth() / 2.f, 200.f), 100.f));
	Enemy* e = new Enemy(game, mStageSpawn.front());

	mEnemies.push_back(e);

}

GameMainState::~GameMainState() {
	for (auto& a : mPlayerBullets)
		delete a;
	mPlayerBullets.clear();
}

bool GameMainState::handleEvent(sf::Event event) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Left:
			mPlayer.setupAnimation(0, 64, 32, 32, 3, 0.5f);
			break;
		case sf::Keyboard::Right:
			mPlayer.setupAnimation(0, 32, 32, 32, 3, 0.5f);
			break;
		case sf::Keyboard::LShift:
			mPlayer.isFocused = true;
			break;
		case sf::Keyboard::Z:
			mPlayer.isShooting = true;
			break;
		case sf::Keyboard::Escape:
			signalStatePush(states::StatesID::Pause);
			mPlayer.isFocused = false;
			mPlayer.isShooting = false;
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::Left:
			mPlayer.setupAnimation(0, 0, 32, 32, 3, 0.5f);
			break;
		case sf::Keyboard::Right:
			mPlayer.setupAnimation(0, 0, 32, 32, 3, 0.5f);
			break;
		case sf::Keyboard::LShift:
			mPlayer.isFocused = false;
			break;
		case sf::Keyboard::Z:
			mPlayer.isShooting = false;
			break;
		
		}
	}
	return true;
}


void GameMainState::setBulletGraphic(EntityRenderer& renderer, Bullet* bul, BulletType graphic) {
	// 4 quad elements that will contain bullet's position and texture coordinate
	sf::Vertex quad[4];
	switch (graphic) {
	case BulletType::PlayerMain:
		quad[0].texCoords = sf::Vector2f(2.f, 100.f); quad[1].texCoords = sf::Vector2f(7.f, 100.f);
		quad[2].texCoords = sf::Vector2f(7.f, 108.f); quad[3].texCoords = sf::Vector2f(2.f, 108.f);
		quad[0].position = sf::Vector2f(bul->getPosition().x - 2.f, bul->getPosition().y + 4.f);
		quad[1].position = sf::Vector2f(bul->getPosition().x + 2.f, bul->getPosition().y + 4.f);
		quad[2].position = sf::Vector2f(bul->getPosition().x + 2.f, bul->getPosition().y - 4.f);
		quad[3].position = sf::Vector2f(bul->getPosition().x - 2.f, bul->getPosition().y - 4.f);
		bul->setupCollider(5.f);
		break;
	case BulletType::sBulletRed:
	
		quad[0].texCoords = sf::Vector2f(0.f, 1.f); quad[1].texCoords = sf::Vector2f(8.f, 1.f);
		quad[2].texCoords = sf::Vector2f(8.f, 9.f); quad[3].texCoords = sf::Vector2f(0.f, 9.f);
		quad[0].position = sf::Vector2f(bul->getPosition().x - 4.f, bul->getPosition().y + 4.f);
		quad[1].position = sf::Vector2f(bul->getPosition().x + 4.f, bul->getPosition().y + 4.f);
		quad[2].position = sf::Vector2f(bul->getPosition().x + 4.f, bul->getPosition().y - 4.f);
		quad[3].position = sf::Vector2f(bul->getPosition().x - 4.f, bul->getPosition().y - 4.f);
		bul->setupCollider(4.f);
		break;
	case BulletType::mBulletRed:

		quad[0].texCoords = sf::Vector2f(1.f, 13.f); quad[1].texCoords = sf::Vector2f(13.f, 13.f);
		quad[2].texCoords = sf::Vector2f(13.f, 26.f); quad[3].texCoords = sf::Vector2f(1.f, 26.f);
		quad[0].position = sf::Vector2f(bul->getPosition().x - 6.f, bul->getPosition().y + 6.f);
		quad[1].position = sf::Vector2f(bul->getPosition().x + 6.f, bul->getPosition().y + 6.f);
		quad[2].position = sf::Vector2f(bul->getPosition().x + 6.f, bul->getPosition().y - 6.f);
		quad[3].position = sf::Vector2f(bul->getPosition().x - 6.f, bul->getPosition().y - 6.f);
		bul->setupCollider(6.f);
		break;
	case BulletType::rBulletRed:
		quad[0].texCoords = sf::Vector2f(0.f, 30.f); quad[1].texCoords = sf::Vector2f(16.f, 30.f);
		quad[2].texCoords = sf::Vector2f(16.f, 46.f); quad[3].texCoords = sf::Vector2f(0.f, 46.f);
		quad[0].position = sf::Vector2f(bul->getPosition().x - 8.f, bul->getPosition().y + 8.f);
		quad[1].position = sf::Vector2f(bul->getPosition().x + 8.f, bul->getPosition().y + 8.f);
		quad[2].position = sf::Vector2f(bul->getPosition().x + 8.f, bul->getPosition().y - 8.f);
		quad[3].position = sf::Vector2f(bul->getPosition().x - 8.f, bul->getPosition().y - 8.f);
		bul->setupCollider(8.f);
		break;
	case BulletType::lBulletRed:
		quad[0].texCoords = sf::Vector2f(0.f, 50.f); quad[1].texCoords = sf::Vector2f(26.f, 50.f);
		quad[2].texCoords = sf::Vector2f(26.f, 76.f); quad[3].texCoords = sf::Vector2f(0.f, 76.f);
		quad[0].position = sf::Vector2f(bul->getPosition().x - 13.f, bul->getPosition().y + 13.f);
		quad[1].position = sf::Vector2f(bul->getPosition().x + 13.f, bul->getPosition().y + 13.f);
		quad[2].position = sf::Vector2f(bul->getPosition().x + 13.f, bul->getPosition().y - 13.f);
		quad[3].position = sf::Vector2f(bul->getPosition().x - 13.f, bul->getPosition().y - 13.f);
		bul->setupCollider(13.f);
		break;
	case BulletType::aBulletRed:
		quad[0].texCoords = sf::Vector2f(5.f, 113.f); quad[1].texCoords = sf::Vector2f(17.f, 113.f);
		quad[2].texCoords = sf::Vector2f(17.f, 125.f); quad[3].texCoords = sf::Vector2f(5.f, 125.f);
		quad[0].position = sf::Vector2f(bul->getPosition().x - 6.f, bul->getPosition().y + 6.f);
		quad[1].position = sf::Vector2f(bul->getPosition().x + 6.f, bul->getPosition().y + 6.f);
		quad[2].position = sf::Vector2f(bul->getPosition().x + 6.f, bul->getPosition().y - 6.f);
		quad[3].position = sf::Vector2f(bul->getPosition().x - 6.f, bul->getPosition().y - 6.f);
		bul->setupCollider(6.f);
		break;
	default:
		bul->setupCollider(0.f);
		break;
	}
	sf::Transform rotation;
	rotation.rotate(bul->getAngle() -90.f, bul->getPosition());
	quad[0].position = rotation.transformPoint(quad[0].position);
	quad[1].position = rotation.transformPoint(quad[1].position);
	quad[2].position = rotation.transformPoint(quad[2].position);
	quad[3].position = rotation.transformPoint(quad[3].position);

	renderer.mVertices.push_back(quad[0]);
	renderer.mVertices.push_back(quad[1]);
	renderer.mVertices.push_back(quad[2]);
	renderer.mVertices.push_back(quad[3]);
}

void GameMainState::createBullet(std::function<void(Bullet&)>& bulScript, std::vector<Bullet*>& vec, EntityRenderer& renderer, sf::Vector2f pos, float speed, float angle, BulletType graphic, float delay, float acceleration, float angular ){
	sf::Vector2f dir(cosf(angle * DEGTORAD), sinf(angle * DEGTORAD));
	Bullet* bul = new Bullet(*getPointerToGame(), pos, dir, speed, angle, graphic, delay);
	bul->setAcceleration(acceleration);
	bul->setAngularMomentum(angular);
	bul->setupScript(bulScript);
	setBulletGraphic(renderer, bul, graphic);
	vec.push_back(std::move(bul));
}

void GameMainState::deleteBullets(std::vector<Bullet*>& vec, EntityRenderer& renderer, size_t index) {
	auto bulIter = vec.begin() + index;
	auto renIter = renderer.mVertices.begin() + (index * 4);
	vec.erase(bulIter);
	renderer.mVertices.erase(renIter, renIter + 4);
}

void GameMainState::updatePlayerBullets(sf::Time deltatime){
	for (size_t i = 0; i < mPlayerBullets.size(); ++i) {
		sf::Transform translation; // get transform of previous angle and position 
		float oldAngle = mPlayerBullets[i]->getAngle();
		sf::Vector2f oldPos = mPlayerBullets[i]->getPosition();
		mPlayerBullets[i]->update(deltatime); // update bullet
		translation.translate(mPlayerBullets[i]->getPosition() - oldPos).rotate(mPlayerBullets[i]->getAngle() - oldAngle, mPlayerBullets[i]->getPosition()); // get the transform of current bullet
		sf::Vertex* quad = &mPlayerBulletRenderer.mVertices[i * 4]; // and update it
		quad[0].position = translation.transformPoint(quad[0].position);
		quad[1].position = translation.transformPoint(quad[1].position);
		quad[2].position = translation.transformPoint(quad[2].position);
		quad[3].position = translation.transformPoint(quad[3].position);
		//check for enemy collision
		for (auto& a : mEnemies) {
			if (mPlayerBullets[i]->isColliding(*a)) {
				mPlayerBullets[i]->setAlive(false);
			}
		}
		if (!mPlayerBullets[i]->isAlive()) { // delete bullet if it's not alive
			deleteBullets(mPlayerBullets, mPlayerBulletRenderer, i);
			--i;
		}
	}
	
}

void GameMainState::updateEnemyBullets(sf::Time deltatime) {
	for (size_t i = 0; i < mEnemyBullets.size(); ++i) {
		sf::Transform translation; // get transform of previous angle and position 
		float oldAngle = mEnemyBullets[i]->getAngle();
		sf::Vector2f oldPos = mEnemyBullets[i]->getPosition();
		mEnemyBullets[i]->update(deltatime); // update bullet
		translation.translate(mEnemyBullets[i]->getPosition() - oldPos).rotate(mEnemyBullets[i]->getAngle() - oldAngle, mEnemyBullets[i]->getPosition()); // get the transform of current bullet
		sf::Vertex* quad = &mEnemyBulletRenderer.mVertices[i * 4]; // and update it
		quad[0].position = translation.transformPoint(quad[0].position);
		quad[1].position = translation.transformPoint(quad[1].position);
		quad[2].position = translation.transformPoint(quad[2].position);
		quad[3].position = translation.transformPoint(quad[3].position);
		//check for enemy collision
		if (mEnemyBullets[i]->isColliding(mPlayer) && !mPlayer.isInvincible) {
			mEnemyBullets[i]->setAlive(false);
		}
		if (!mEnemyBullets[i]->isAlive()) { // delete bullet if it's not alive
			deleteBullets(mEnemyBullets, mEnemyBulletRenderer, i);
			--i;
		}
	}
}

bool GameMainState::update(sf::Time deltaTime) {
	//update player
	mPlayer.update(deltaTime);
	float playerTimer;
	if (mPlayer.isShooting) {
		if (mPlayer.isFocused)
			playerTimer = 0.05f;
		else
			playerTimer = 0.1f;
		if (mPlayer.getTimer() <= 0.f) {
			//create two bullets going up 
			createBullet(moveStraight, mPlayerBullets, mPlayerBulletRenderer, sf::Vector2f(mPlayer.getPosition().x - 5.f, mPlayer.getPosition().y), 720.f * deltaTime.asSeconds(), -90, BulletType::PlayerMain);
			createBullet(moveStraight, mPlayerBullets, mPlayerBulletRenderer, sf::Vector2f(mPlayer.getPosition().x + 5.f, mPlayer.getPosition().y), 720.f * deltaTime.asSeconds(), -90, BulletType::PlayerMain);
			mPlayer.setTimer(playerTimer);
		}
	}
	//update bullets and check for collision
	updatePlayerBullets(deltaTime);
	for (auto& a : mEnemies) {
		a->update(deltaTime);
	}
	updateEnemyBullets(deltaTime);

	mDebugText.setString("No. of bullets: " + std::to_string(mEnemyBullets.size()));
	mGlobalTime += deltaTime.asSeconds();
	return true;
}

void GameMainState::render(sf::RenderTarget& app) {
	mPlayer.draw(app);
	for (auto& a : mEnemies) { a->draw(app); }
	app.draw(mPlayerBulletRenderer);
	app.draw(mEnemyBulletRenderer);
	app.draw(mDebugText);
}

