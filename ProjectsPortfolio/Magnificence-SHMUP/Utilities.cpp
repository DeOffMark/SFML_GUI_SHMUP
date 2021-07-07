#include "Utilities.hpp"

float dot(sf::Vector2f& a, sf::Vector2f& b) { //dot product
    return a.x * b.x + a.y * b.y;
}

float length(sf::Vector2f& a) { // vector's length
    if (a.x == 0.f && a.y == 0.f) return 0.f;
    return std::sqrtf(a.y * a.y + a.x * a.x);
}

float length2(sf::Vector2f& a) { // vector's length squared 
    return a.y * a.y + a.x * a.x;
}

sf::Vector2f normalize(sf::Vector2f& a) { // returns vector with length of 1;
    return a / length(a);
}

int clamp(int value, int min, int max) {
    return std::max(min, std::min(max, value));
}

float clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}