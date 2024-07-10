#include "Bullet.h"

Bullet::Bullet(unsigned int imageId_, float radius_){
	body = new Body();
	body->setRadius(radius_);
	imageId = imageId_;
}

Bullet::~Bullet(){
	delete body;
}

void Bullet::Render(GameManager* game){
	float gunScaleX = 0.04f;
	float gunScaleY = 0.04f;
	ResourceManager::getInstance()->RenderImage(game, imageId, body->getPos(), Vec3(gunScaleX, gunScaleY, 0.0f), angle);
}

void Bullet::Update(float deltaTime_){
	body->Update(deltaTime_);
}

void Bullet::setDir(Vec3 dir){
	angle = std::atan2(-dir.y, dir.x) * (180.0f / M_PI);
	body->vel = VMath::normalize(dir) * speed;
}

void Bullet::setPos(Vec3 pos_){
	body->setPos(pos_);
}

bool Bullet::OutOfBounds(float xAxis, float yAxis){
	auto pos = body->getPos();
	if (pos.x > xAxis || pos.x < -xAxis || pos.y > yAxis || pos.y < -yAxis)
		return true;
	return false;
}
