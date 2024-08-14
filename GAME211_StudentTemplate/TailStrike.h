#pragma once
#include "GameObject.h"

class TailStrike : public GameObject {
public:
	TailStrike(GameManager* game_) : GameObject(game_) {
		//body->setPos(Vec3(7, 7, 0));
		scale = Vec3(0.1, 0.1, 0.1);
		imageId = ResourceManager::getInstance()->AddImage(game_, "Art/TailStrike.PNG");

		coliders.push_back(new CircleCollider(Vec3(0.4, 0.0, 0), 2.45));

	}

	void Render() {
		GameObject::Render();
	}
};