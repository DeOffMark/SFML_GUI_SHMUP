#include "State.h"
#include "Game.h"

State::Resources::Resources(ResourceHolder<sf::Texture>& textures, ResourceHolder<sf::Font>& fonts) : textures(&textures), fonts(&fonts) {
}

State::State(Game& game, Resources resources) : mGame(&game), mResources(resources) {
}

Game* State::getPointerToGame() { return mGame; }

void State::signalStatePush(states::StatesID id) { mGame->pushState(id); }
void State::signalStatePop() { mGame->popState(); }
void State::signalStatesClear() { mGame->clearStates(); }

State::Resources State::getResources() const { return mResources; }