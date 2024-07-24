#pragma once
#include "Body.h"
#include <vector>
#include "Shapes.h"

struct CircleCollider {
	float radius;
	Vec3 pos;

	CircleCollider(Vec3 pos = Vec3(), float radius = 1.0f) : pos(pos), radius(radius) {}

	/// This is for debuging only, rendering should be done inside the 
	/// object that owns this, since this pos is supposed to be reletive 
	/// to the pos of the parent
	void Render(GameManager* game, Vec4 color = Vec4(0,255,0,255)) {
		Shapes::DrawCircle(game, pos, radius, color);
	}
};

class Collision {
public:
	static bool Circle_Circle_Collision(Body* b1, Body* b2, GameManager* game) {
		float maxDistance = b1->getRadius() + b2->getRadius();
		float distance = VMath::distance(b1->getPos(), b2->getPos());
		distance = Util::GameToScreenCoords(Vec3(distance, distance, distance), game).x;
		if (distance <= maxDistance) {
			return true;
		}
		return false;
	}

	static bool Circle_Circle_Collision(CircleCollider b1, CircleCollider b2, GameManager* game) {
		float maxDistance = b1.radius + b2.radius;
		float distance = VMath::distance(b1.pos, b2.pos);
		maxDistance = Util::GameToScreenCoords(Vec3(maxDistance, maxDistance, maxDistance), game).x;
		distance = Util::GameToScreenCoords(Vec3(distance, distance, distance), game).x;
		if (distance <= maxDistance) {
			return true;
		}
		return false;
	}
};