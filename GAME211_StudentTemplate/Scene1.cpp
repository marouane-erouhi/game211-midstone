#include "Scene1.h"
#include <VMath.h>
#include "ResourceManager.h"
#include "Shapes.h"

using namespace std;

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.f;
	yAxis = 15.0f;
}

Scene1::~Scene1(){
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);

	mouse.leftButtonDown = false;
	mouse.rightButtonDown = false;

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Add desert image from file
	desertImageID = ResourceManager::getInstance()->AddImage(game, "Art/Desert.png");
	bulletImageID = ResourceManager::getInstance()->AddImage(game, "Art/Bullet Scaled.PNG");

	boss1 = new Boss1(game);
	boss1->setPos(Vec3(20,5,0));

	callOfDinosaurs = new CallOfDinosaurs(game);
	callOfDinosaurs->setPos(Vec3(12.5,7.5,0));
	tailStrike = new TailStrike(game);

	// Set player image to PacMan
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("Art/PlayerWithGun.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	bullet_timeSinceLastFire += deltaTime;

	// check collisions
	// player and bullets for test


	if (mouse.leftButtonDown) {
		if (bullet_timeSinceLastFire >= bulletCooldown) {
			bullet_timeSinceLastFire = 0.0f;
			Vec3 playerScreenCoords = projectionMatrix * game->getPlayer()->getPos();
			auto playerPos = game->getPlayer()->getPos();
			Vec3 m = mouse.getGameCoords(game);

			Vec3 dir(m.x - playerPos.x, m.y - playerPos.y, 0);

			// create bullet
			Bullet* b = new Bullet(bulletImageID, 0.6f);
			// offset slighly infrot of the player
			b->setPos(playerPos + VMath::normalize(dir) * 2.50f);
			b->setDir(dir);// speed

			bullets.push_back(b);
		}
	}

	// bullets update
	for (int i = bullets.size() - 1; i >= 0; --i) {
		Bullet* bullet = bullets.at(i);
		if (bullet->OutOfBounds(xAxis, yAxis)) {
			// destroy when out of screen bounds
			bullets.erase(bullets.begin() + i);
		}
		else {
			bullet->Update(deltaTime);
		}
	}

	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Declare variables for desert's scale
	float desertScaleX = 1000 / 967;
	float desertScaleY = 600 / 580;

	// Declare variables for the gun's scale
	float gunScaleX = 0.04f;
	float gunScaleY = 0.04f;

	// background image
	ResourceManager::getInstance()->RenderImage(game, desertImageID, Vec3(12.5f, 7.5f, 0), Vec3(desertScaleX, desertScaleY, 0.0f));

	tailStrike->Render();
	callOfDinosaurs->Render();
	boss1->Render();

	for (Bullet* bullet : bullets) {
		bullet->Render(game);
		auto body = bullet->getBody();
		Shapes::DrawCircle(game, body->getPos(), body->getRadius());
	}
	
	Vec3 playerScreenCoords = projectionMatrix * game->getPlayer()->getPos();

	SDL_RenderDrawLine(renderer, mouse.x,mouse.y, playerScreenCoords.x, playerScreenCoords.y);
	
	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	game->getPlayer()->HandleEvents(event);
	mouse.update(event);

}
