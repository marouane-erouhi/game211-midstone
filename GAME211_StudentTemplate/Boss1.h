#pragma once
#include "GameObject.h"

class Boss1 : public GameObject {
public:
	Boss1(GameManager* game_) : GameObject(game_) {
		//body->setPos(Vec3(7, 7, 0));

		imageId = ResourceManager::getInstance()->AddImage(game_, "Art/FirstBoss.PNG");

		coliders.push_back(new CircleCollider(Vec3(-0.4, -0.4, 0), 3));
		coliders.push_back(new CircleCollider(Vec3(-3.7, 2, 0), 1.6));
		coliders.push_back(new CircleCollider(Vec3(3.7, -0.7, 0), 1.3));
	}

	void Render() {
		GameObject::Render();
	}
};