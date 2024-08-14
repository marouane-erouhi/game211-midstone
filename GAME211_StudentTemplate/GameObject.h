#pragma once
#include "Body.h"
#include <vector>
#include "ResourceManager.h"
#include "Collision.h"

class GameObject {
protected:
	GameManager* game;
	Body* body;
	unsigned int imageId;
	std::vector<CircleCollider*> coliders;

	float speed;
	float angle = 0.0f;
	Vec3 scale = Vec3(0.2, 0.22, 0.0);


public:
	GameObject(GameManager* game);

	void Render();

	void setPos(Vec3 pos_) {
		body->setPos(pos_);
	}
};