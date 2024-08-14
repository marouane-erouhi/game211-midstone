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
	std::vector<CircleCollider*> coliders;

	float speed;
	float angle = 0.0f;
	Vec3 scale = Vec3(0.2, 0.22, 0.0);

    float maxSpeed = 3.0;

public:
	GameObject(GameManager* game);

	void Render();
	void Update(float deltaTime) {
		body->Update(deltaTime);
	}

	void setPos(Vec3 pos_) {
		body->setPos(pos_);
	}
    void HandleEvents(const SDL_Event& event) {
        // used for debugging 
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
                body->vel.y = 1 * maxSpeed;
                break;
            case SDL_SCANCODE_A:
                body->vel.x = -1 * maxSpeed;
                break;
            case SDL_SCANCODE_S:
                body->vel.y = -1 * maxSpeed;
                break;
            case SDL_SCANCODE_D:
                body->vel.x = 1 * maxSpeed;
                break;
            }
        }

        if (event.type == SDL_KEYUP && event.key.repeat == 0) {
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
                body->vel.y = 0;
                break;
            case SDL_SCANCODE_A:
                body->vel.x = 0;
                break;
            case SDL_SCANCODE_S:
                body->vel.y = 0;
                break;
            case SDL_SCANCODE_D:
                body->vel.x = 0;
                break;
            }
        }
    }
};