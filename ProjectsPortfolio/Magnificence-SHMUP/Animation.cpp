#include "Animation.h"

Animation::Animation() = default;

Animation::Animation(int x, int y, int w, int h, int count, float speed) {
	mFrame = 0;
	mSpeed = speed;

	for (int i = 0; i < count; ++i) {
		mFrames.push_back(sf::IntRect(x + (i * w), y, w, h));
	}

}

void Animation::update() {
	mFrame += mSpeed;
	if (mFrame >= mFrames.size()) mFrame -= mFrames.size();
}

sf::IntRect Animation::getCurrentFrame() {
	return mFrames[int(mFrame)];
}

bool Animation::isEnd() {
	return mFrame + mSpeed >= mFrames.size();
}

void Animation::addFrame(int x, int y, int w, int h) {
	mFrames.push_back(sf::IntRect(x, y, w, h));
}

void Animation::addFrames(int x, int y, int w, int h, int count) {
	for (int i = 0; i < count; ++i) {
		mFrames.push_back(sf::IntRect(x + (i * w), y, w, h));
	}
}

void Animation::clearFrames() {
	mFrames.clear();
}