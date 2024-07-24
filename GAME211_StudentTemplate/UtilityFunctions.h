#pragma once
#include <MMath.h>
#include "GameManager.h"
using namespace MATH;


Vec3 GameToScreenCoords(Vec3 vec, GameManager* game){
    // game to screen coords
    return game->getProjectionMatrix() * vec;
}

//Vec3