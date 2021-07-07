#pragma once 
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "StateIdentifiers.h"
#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace sf {
	class Texture;
	class Font;
	class RenderTarget;
}
class Game;

class State {
public:
	typedef std::unique_ptr<State> StatePtr;

	struct Resources {
		Resources(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts);
		ResourceHolder<sf::Texture>* textures;
		ResourceHolder<sf::Font>* fonts;
	};

public:
	State(Game& game, Resources res);
	virtual ~State() = default;

	
	virtual bool handleEvent(sf::Event) = 0;
	virtual bool update(sf::Time) = 0;
	virtual void render(sf::RenderTarget&) = 0;

protected:
	Game* getPointerToGame();
	void signalStatePush(states::StatesID id);
	void signalStatePop();
	void signalStatesClear();

	Resources getResources() const;

private:
	Game* mGame;
	Resources mResources;

};