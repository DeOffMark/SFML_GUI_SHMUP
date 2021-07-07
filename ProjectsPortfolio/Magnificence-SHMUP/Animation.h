#pragma once
#include <vector>
#include <SFML/Graphics/Rect.hpp>
//class that contains information about the boundary position for AnimatedEntity' sprite
class Animation {
public:

	Animation();

	Animation(int x, int y, int w, int h, int count, float speed); // x,y, w, h for bounds, counts for how many sprites and speed is its frequency

	void update();

	sf::IntRect getCurrentFrame();

	void addFrames(int x, int y, int w, int h, int count); // add multiple frames with consecutive order to the right of the texture coordinates

	void addFrame(int x, int y, int w, int h); // add one frame

	void clearFrames();

	bool isEnd(); // checks if you're at the last frame

protected:
	float mFrame, mSpeed;
	std::vector<sf::IntRect> mFrames;
};