#pragma once
#include "Body.h"
#include "ResourceManager.h"

class Bullet {
	Body* body;
	unsigned int imageId;
	float speed = 3.0f;
	float angle = 0.0f;

public:
	Bullet(unsigned int imageId_);
	~Bullet();

	void Render(GameManager* game);
	void Update(float deltaTime_);
	void setDir(Vec3 dir_);
	void setPos(Vec3 pos_);
	bool OutOfBounds(float xAxis, float yAxis);
};