#pragma once
#include "Body.h"

class Collision {
public:
	static bool Circle_Circle_Collision(Body* b1, Body* b2) {
		float maxDistance = b1->getRadius() + b2->getRadius();
		float distance = VMath::distance(b1->getPos(), b2->getPos());
		if (distance <= maxDistance) {
			return true;
		}
		return false;
	}
};