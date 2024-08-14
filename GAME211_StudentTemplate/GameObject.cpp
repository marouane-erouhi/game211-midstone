#include "GameObject.h"

GameObject::GameObject(GameManager* game_)
{
	game = game_;
	body = new Body();
	
}

void GameObject::Render()
{
	ResourceManager::getInstance()->RenderImage(game, imageId, body->getPos(), Vec3(scale.x, scale.y, 0.0f), angle);

	if (game->isColliderDisplay()) {
		// render collider
		for (auto collider : coliders) {
			Shapes::DrawCircle(game, body->getPos() + collider->pos, collider->radius);
		}
	}
}
