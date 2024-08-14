#include "CollisionTestScene.h"
#include <VMath.h>
#include "ResourceManager.h"
#include "Shapes.h"

using namespace std;

CollisionTestScene::CollisionTestScene(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.f;
	yAxis = 15.0f;
}

CollisionTestScene::~CollisionTestScene() {
}

bool CollisionTestScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	mouse.leftButtonDown = false;
	mouse.rightButtonDown = false;

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// collider reletive pos for the non centered bullet sprite: Vec3(0.2, 0.1, 0)
	

	
	test_collider.pos = Vec3(5, 7, 0);
	test_collider.radius = 0.6;




	imageId = ResourceManager::getInstance()->AddImage(game, "Art/Bullet Scaled.PNG");



	/// Mouse testing
	static_coll.pos = Vec3(12, 7, 0);
	mouseColl.pos = Vec3();
	static_coll.radius = mouseColl.radius = 1.0f;

	return true;
}

void CollisionTestScene::OnDestroy() {}

void CollisionTestScene::Update(const float deltaTime) {

	mouseColl.pos = mouse.getGameCoords(game);

	if (Collision::Circle_Circle_Collision(static_coll, mouseColl, game)) {
		color = Vec4(255, 0, 255, 255);
	}
	else {
		color = Vec4(0, 255, 0, 255);

	}

}

void CollisionTestScene::Render() {
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);


	static_coll.Render(game, color);
	mouseColl.Render(game, color);

	ResourceManager::getInstance()->RenderImage(game, imageId, Vec3(10,7,1), Vec3(0.06, 0.06, 0.06));


	test_collider.Render(game, Vec4(255,0,255,255));

	SDL_RenderPresent(renderer);
}

void CollisionTestScene::HandleEvents(const SDL_Event& event)
{
	mouse.update(event);

	// used for adjusting the collider size and position at runtime
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_RIGHT:
			test_collider.pos.x += 0.1;
			break;
		case SDL_SCANCODE_LEFT:
			test_collider.pos.x -= 0.1;
			break;
		case SDL_SCANCODE_UP:
			test_collider.pos.y += 0.1;
			break;
		case SDL_SCANCODE_DOWN:
			test_collider.pos.y -= 0.1;
			break;

		case SDL_SCANCODE_EQUALS:// plus
			test_collider.radius += 0.1;
			break;
		case SDL_SCANCODE_MINUS:// minus
			test_collider.radius -= 0.1;
			break;
		}
		cout << "pos: " << test_collider.pos.x << " - " << test_collider.pos.y << "\tradius: " << test_collider.radius << endl;
	}

}
