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

	

	col1.pos = Vec3(12, 7, 0);
	col2.pos = Vec3();
	col1.radius = col2.radius = 25.0f;

	return true;
}

void CollisionTestScene::OnDestroy() {}

void CollisionTestScene::Update(const float deltaTime) {

	col2.pos = mouse.getGameCoords(game);

	if (Collision::Circle_Circle_Collision(col1, col2)) {
		cout << "collision" << endl;
	}

}

void CollisionTestScene::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);


	col1.Render(game);
	col2.Render(game);

	SDL_RenderPresent(renderer);
}

void CollisionTestScene::HandleEvents(const SDL_Event& event)
{
	mouse.update(event);

}
