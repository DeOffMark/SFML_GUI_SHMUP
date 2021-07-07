#pragma once
#include "State.h"
class LoadingState : public State {
public:
	LoadingState(Game& game, Resources res);
	~LoadingState();
	bool handleEvent(sf::Event event) override;
	bool update(sf::Time deltaTime) override;
	void render(sf::RenderTarget& app) override;
private:
	sf::Text mLoadingText;
};