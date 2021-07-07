#include "Game.h"

int main() {
	srand(unsigned int(std::time(0)));
	Game game("Project Shmup",640, 480, 2, 2);
	game.run();
	return 0;
}