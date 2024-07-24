#pragma once
#include "Body.h"
#include "ResourceManager.h"
#include "Collision.h"

class Bullet {
	Body* body;
	unsigned int imageId;
	float speed = 3.0f;
	float angle = 0.0f;

	// location reletive to parent location
	CircleCollider collider;

public:
	Bullet(unsigned int imageId_, float radius_);
	~Bullet();

	void Render(GameManager* game, Vec3 scale=Vec3(0.04, 0.04,0));
	void Update(float deltaTime_);
	void setDir(Vec3 dir_);
	void setPos(Vec3 pos_);
	bool OutOfBounds(float xAxis, float yAxis);
	Body* getBody() { return body; }
	CircleCollider getCollider_Absolute();
	void setCollider(CircleCollider coll);
};