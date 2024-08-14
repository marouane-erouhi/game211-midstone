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

	// location reletive to parent location
	std::vector<CircleCollider*> coliders;

	float speed = 3.0;
	float angle = 0.0f;
	Vec3 scale = Vec3(0.2, 0.22, 0.0);

    float maxSpeed = 3.0;

public:
	GameObject(GameManager* game);
	~GameObject();

	void Render();
	void Update(float deltaTime);

    void setPos(Vec3 pos_);
	void HandleEvents(const SDL_Event& event);
    void setDir(Vec3 dir_);
};