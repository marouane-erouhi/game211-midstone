#pragma once

#include <MMath.h>
#include "Scene.h"
#include "Mouse.h"
#include "Bullet.h"

using namespace MATH;

class CollisionTestScene : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4     inverseProjection;	// set in OnCreate()

	Mouse mouse;

	CircleCollider static_coll, mouseColl;
	Vec4 color = Vec4(0,255,0,255);



	CircleCollider test_collider;


public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	CollisionTestScene(SDL_Window* sdlWindow_, GameManager* game_);
	~CollisionTestScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};
