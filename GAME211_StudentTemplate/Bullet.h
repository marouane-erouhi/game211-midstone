#pragma once
#include "Body.h"
#include "ResourceManager.h"
#include "Collision.h"
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet(GameManager* game_) : GameObject(game_) {
		imageId = ResourceManager::getInstance()->AddImage(game_, "Art/Bullet Scaled.PNG");
		scale = Vec3(0.06, 0.06, 0.06);
		coliders.push_back(new CircleCollider(Vec3(0,0, 0), 0.9));
	}

	bool OutOfBounds();
	Body* getBody() { return body; }
};