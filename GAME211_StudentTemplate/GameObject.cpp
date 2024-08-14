#include "GameObject.h"

GameObject::GameObject(GameManager* game_)
{
	game = game_;
	body = new Body();
	
}

GameObject::~GameObject(){
    delete body;
    for (auto collider : coliders) {
        delete collider;
    }
    coliders.clear();
}

void GameObject::Render()
{
	ResourceManager::getInstance()->RenderImage(game, imageId, body->getPos(), Vec3(scale.x, scale.y, scale.z), angle);

	if (game->isColliderDisplay()) {
		// render collider
		for (auto collider : coliders) {
			Shapes::DrawCircle(game, body->getPos() + collider->pos, collider->radius);
		}
	}
}

void GameObject::Update(float deltaTime) {
    body->Update(deltaTime);
}

void GameObject::setPos(Vec3 pos_){
	body->setPos(pos_);
}

void GameObject::HandleEvents(const SDL_Event& event) {
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

void GameObject::setDir(Vec3 dir_){
	angle = std::atan2(-dir_.y, dir_.x) * (180.0f / M_PI);
	body->vel = VMath::normalize(dir_) * speed;
}
