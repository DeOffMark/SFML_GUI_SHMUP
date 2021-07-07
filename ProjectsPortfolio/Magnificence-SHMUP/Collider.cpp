#include "Collider.h"

Collider::Collider() {
	mType = ColliderType::Radial;
	mNodes.push_back(1.f);
}

Collider::Collider(float radius) {
	mType = ColliderType::Radial;
	mNodes.push_back(radius);
}

Collider::Collider(float length, float width) {
	mType = ColliderType::Linear;
	mNodes.push_back(length);
	mNodes.push_back(width);
}

