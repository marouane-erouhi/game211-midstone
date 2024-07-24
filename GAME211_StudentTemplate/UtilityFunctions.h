#pragma once
#include "GameManager.h"

struct Util {
	static Vec3 GameToScreenCoords(Vec3 a, GameManager* game) {
		return game->getProjectionMatrix() * a;
	}
	static Vec3 GameToScreenCoords(float a, GameManager* game) {
		return game->getProjectionMatrix() * Vec3(a,a,a);
	}

	static Vec3 ScreentoGameCoords(Vec3 a, GameManager* game) {
		return MMath::inverse(game->getProjectionMatrix()) * a;
	}
	static Vec3 ScreentoGameCoords(float a, GameManager* game) {
		return MMath::inverse(game->getProjectionMatrix()) * Vec3(a,a,a);
	}
};
