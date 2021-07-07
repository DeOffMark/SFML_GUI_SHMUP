#include "Game.h"
#include "GameMainState.h"
#include "PauseState.h"
#include "LoadingState.h"
#include <thread>
Game::Game() : mApp(sf::VideoMode(640, 480), "Standard App", sf::Style::Default), mTextures(), mFonts(), mResources(mTextures, mFonts) {
	
	mApp.setFramerateLimit(120);
	mWidth = mApp.getSize().x;
	mHeight = mApp.getSize().y;
	mFutureState = nullptr;
	
	mStates.push_back(createState(states::StatesID::MainGame));
}

Game::PendingChange::PendingChange(Signal signal, states::StatesID ID = states::StatesID::None) : signal(signal), stateID(ID) {
}

Game::Game(std::string name, const int width, const int height, int scaleX, int scaleY) :
	mApp(sf::VideoMode(width, height), name, sf::Style::Default), mTextures(), mFonts(), mResources(mTextures, mFonts) {
	
	mWidth = width;
	mHeight = height;
	mApp.setSize(sf::Vector2u(mApp.getSize().x * scaleX, mApp.getSize().y * scaleY));
	mApp.setPosition(sf::Vector2i(mApp.getPosition().x / scaleX, 0));
	mFutureState = nullptr;
	//load resources
	mTextures.load("tPlayer", "Media/SpritesPlayer.png");
	mTextures.load("tEnemy", "Media/asset.png"); // placeholder for enemy sprites
	mTextures.load("tEnemyBullets", "Media/SpritesShots.png");
	mFonts.load("tPause", "Media/Arkitech Bold.ttf");
	mFonts.load("tDebug", "Media/Sansation.ttf");
	
	mStates.push_back(createState(states::StatesID::MainGame));
	
}

const sf::RenderWindow& Game::getWindow() const { return mApp; }
int Game::getWindowWidth() { return mWidth; }
int Game::getWindowHeight() { return mHeight; }

void Game::run() { //setup scenes 
	sf::Time timePerUpdate = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;
	
	while (mApp.isOpen() && !mStates.empty()) { 	//update loop of the scene
		sf::Time deltatime = clock.restart();
		elapsed += deltatime;
		
	
		//event handling
		handleEvent();
		//update scene
		while (elapsed >= timePerUpdate) {
			//update every states until stop sign
			for (auto a = mStates.rbegin(); a != mStates.rend(); ++a) 
				if (!(*a)->update(timePerUpdate)) break;
			applyChanges();
			mApp.setTitle("Project Shmup: " + std::to_string(1.f / elapsed.asSeconds()) + "fps");
			elapsed -= timePerUpdate;
		}
		//render
		mApp.clear();
		for (State::StatePtr& a : mStates)
			a->render(mApp);
		mApp.display();
		
	}
}

void Game::handleEvent() {
	sf::Event event;
	while (mApp.pollEvent(event)) {
		for (auto a = mStates.rbegin(); a != mStates.rend(); ++a)
			if (!(*a)->handleEvent(event)) break;
		applyChanges();
		switch (event.type) {
			// active scene's event handling
			
			//applyChanges();
		case sf::Event::Closed:
			mApp.close();
			break;
		}
	}
}


void Game::pushState(states::StatesID id) { mChanges.push_back(PendingChange(Signal::Push, id)); }
void Game::popState() {mChanges.push_back(PendingChange(Signal::Pop));}
void Game::clearStates() {mChanges.push_back(PendingChange(Signal::Clear));}

State::StatePtr Game::createState(states::StatesID id){
	switch (id) {
	case states::StatesID::MainGame:
		return State::StatePtr(new GameMainState(*this, State::Resources(mTextures, mFonts)));
		break;
	case states::StatesID::Pause:
		return State::StatePtr(new PauseState(*this, State::Resources(mTextures, mFonts)));
		break;
	case states::StatesID::Loading:
		return State::StatePtr(new LoadingState(*this, State::Resources(mTextures, mFonts)));
		break;
	default:
		return State::StatePtr(new LoadingState(*this, State::Resources(mTextures, mFonts)));
		break;
	}
}

void Game::applyChanges() {
	for (PendingChange& p : mChanges) {
		switch (p.signal) {
		case Signal::Push:
			mStates.push_back(createState(p.stateID));
			break;
		case Signal::Pop:
			mStates.pop_back();
			break;
		case Signal::Clear:
			mStates.clear();
			break;
		}
	}
	mChanges.clear();
}

void Game::loadGameState() {
	sf::sleep(sf::seconds(4.f));
	mFutureState = State::StatePtr(new GameMainState(*this, State::Resources(mTextures, mFonts)));
	//mStates.pop_back();
	mStates.push_back(std::move(mFutureState));
}