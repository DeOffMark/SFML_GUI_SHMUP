#include "LoadingState.h"
#include "Game.h"

LoadingState::LoadingState(Game& game, Resources res) : State(game, res) {
	mLoadingText.setFont(res.fonts->get("tPause"));
	mLoadingText.setPosition(float(game.getWindowWidth() - 200), float(game.getWindowHeight() - 100));
	mLoadingText.setCharacterSize(20);
	mLoadingText.setString("Loading...");
}

LoadingState::~LoadingState(){}

bool LoadingState::handleEvent(sf::Event event) {
	return false;
}

bool LoadingState::update(sf::Time deltatime) {
	return false;
}

void LoadingState::render(sf::RenderTarget& app) {
	app.draw(mLoadingText);
}