#pragma once
#include "GameObject.h"

class CallOfDinosaurs : public GameObject {
public:
	CallOfDinosaurs(GameManager* game_) : GameObject(game_) {
		//body->setPos(Vec3(7, 7, 0));
		scale = Vec3(0.3, 0.3, 0.3);

		imageId = ResourceManager::getInstance()->AddImage(game_, "Art/CallOfDinosaurs.PNG");

		coliders.push_back(new CircleCollider(Vec3(-4, 0.0, 0), 2));
		coliders.push_back(new CircleCollider(Vec3(-0.1, 0.0, 0), 2));
		coliders.push_back(new CircleCollider(Vec3(3.8, 0.0, 0), 2));

	}

	void Render() {
		GameObject::Render();
	}
};