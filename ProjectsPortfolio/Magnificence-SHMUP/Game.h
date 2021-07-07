#pragma once

#include <memory>
#include <vector>
#include "State.h"
#include "ResourceHolder.h"

class Game {
public:
	enum class Signal {
		Push = 0, 
		Pop, 
		Clear,
	};
public:
	Game(); 
	Game(std::string name, const int width, const int height, int scaleX, int scaleY); 
		
	void run();

	const sf::RenderWindow& getWindow() const;

	int getWindowWidth();
	int getWindowHeight();
	void handleEvent();

	void loadGameState(); // a thread function to load a state while putting a loading state

	void pushState(states::StatesID id);
	void popState();
	void clearStates();

private:
	struct PendingChange {
		explicit PendingChange(Signal signal, states::StatesID ID);
		Signal signal;
		states::StatesID stateID;
	};
	void applyChanges();
	State::StatePtr createState(states::StatesID id);
	
private:
	ResourceHolder<sf::Texture> mTextures;
	ResourceHolder<sf::Font> mFonts;
	sf::RenderWindow mApp;
	int mWidth;
	int mHeight;
	bool mShouldChange = false; //bool for should we change state

	std::vector<State::StatePtr> mStates; // states that are currently are in use
	State::StatePtr mFutureState;
	State::Resources mResources;
	std::vector<PendingChange> mChanges;
};

