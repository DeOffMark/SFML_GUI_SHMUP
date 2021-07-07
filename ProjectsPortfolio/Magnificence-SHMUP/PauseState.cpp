#include "PauseState.h"
#include "Game.h"
PauseState::PauseState(Game& game, Resources res) : State(game, res) {
	mPauseText.setFont(res.fonts->get("tPause"));
	mPauseText.setPosition(float(game.getWindowWidth()/2), 100.f);
	mPauseText.setCharacterSize(45);
	mPauseText.setString("Paused!");
	mPauseText.setOrigin(mPauseText.getLocalBounds().width / 2, mPauseText.getLocalBounds().height / 2);

	mBack.setSize(sf::Vector2f(float(game.getWindowWidth()), float(game.getWindowHeight())));
	mBack.setFillColor(sf::Color(0, 0, 0, 150));
	mBack.setPosition(0.f, 0.f);
}

PauseState::~PauseState(){}

bool PauseState::handleEvent(sf::Event event){
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			signalStatePop();
			break;
		}
	}
	return false;
}

bool PauseState::update(sf::Time deltatime) {
	return false;
}

void PauseState::render(sf::RenderTarget& app) {
	app.draw(mBack);
	app.draw(mPauseText);
}