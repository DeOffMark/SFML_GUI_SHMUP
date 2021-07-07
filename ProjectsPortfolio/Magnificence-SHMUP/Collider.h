#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

enum class ColliderType{Radial, Linear};

class Collider {
public:
	Collider(); // constructor for standard radial collider with radius 1.f

	Collider(float radius); // constructor for radial collider

	Collider(float length, float width); // constructor for linear collider

	ColliderType mType; 
	std::vector<float> mNodes; // nodes could mean radius, length or width for collider
};