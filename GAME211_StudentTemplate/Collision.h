#pragma once
#include "Body.h"
#include <vector>
#include "Shapes.h"

struct CircleCollider {
	float radius;
	Vec3 pos;

	void Render(GameManager* game) {
		Shapes::DrawCircle(game, pos, radius);
	}
};

class Collision {
public:
	static bool Circle_Circle_Collision(Body* b1, Body* b2) {
		float maxDistance = b1->getRadius() + b2->getRadius();
		float distance = VMath::distance(b1->getPos(), b2->getPos());
		distance = GameToScreenCoords(Vec3(distance, distance, distance), game).x;
		if (distance <= maxDistance) {
			return true;
		}
		return false;
	}

	static bool Circle_Circle_Collision(CircleCollider b1, CircleCollider b2) {
		float maxDistance = b1.radius + b2.radius;
		float distance = VMath::distance(b1.pos, b2.pos);
		if (distance <= maxDistance) {
			return true;
		}
		return false;
	}
};