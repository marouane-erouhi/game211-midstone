#include "Bullet.h"

bool Bullet::OutOfBounds(){
	float xAxis = game->getSceneWidth();
	float yAxis = game->getSceneHeight();

	auto pos = body->getPos();
	if (pos.x > xAxis || pos.x < -xAxis || pos.y > yAxis || pos.y < -yAxis)
		return true;
	return false;
}
