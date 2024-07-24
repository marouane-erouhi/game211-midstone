#include "Bullet.h"

Bullet::Bullet(unsigned int imageId_, float radius_){
	body = new Body();
	//body->setRadius(radius_);
	imageId = imageId_;
	collider = CircleCollider(Vec3(), radius_);
}

Bullet::~Bullet(){
	delete body;
}

void Bullet::Render(GameManager* game, Vec3 scale){
	ResourceManager::getInstance()->RenderImage(game, imageId, body->getPos(), Vec3(scale.x, scale.y, 0.0f), angle);
	
	if (game->isColliderDisplay()) {
		// render collider
		Shapes::DrawCircle(game, body->getPos() + collider.pos, collider.radius);
	}
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

CircleCollider Bullet::getCollider_Absolute() {
	CircleCollider coll = CircleCollider();
	coll.pos = collider.pos + body->getPos();
	return coll;
}
void Bullet::setCollider(CircleCollider coll) {
	collider = coll;
}
