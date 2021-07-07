#pragma once

#include "State.h"

class PauseState : public State {
public:
	PauseState(Game& game, Resources res);
	~PauseState();
	bool handleEvent(sf::Event event) override;
	bool update(sf::Time deltaTime) override;
	void render(sf::RenderTarget& app) override;
private:
	sf::Text mPauseText;
	sf::RectangleShape mBack; // Semi-transparent black background
};