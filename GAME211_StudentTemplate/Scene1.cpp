#include "Scene1.h"
#include <VMath.h>
#include "ResourceManager.h"

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

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Add desert image from file
	int desertImage = ResourceManager::getInstance()->AddImage(game, "Art/Desert.png");

	// add the bullet image from file
	int bulletImage = ResourceManager::getInstance()->AddImage(game, "Art/Bullet.png");
	bulletPos = Vec3(16.0f, 7.5f, 0.0f);
	bullet = new Body();
	SDL_Surface* a = IMG_Load("Art/Bullet.png");
	bullet->setImage(a);
	bullet->setTexture(SDL_CreateTextureFromSurface(renderer, a));

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

	bullet->Update(deltaTime);
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

	// bullet image
	ResourceManager::getInstance()->RenderImage(game, bulletImageID, bullet->getPos(), Vec3(gunScaleX, gunScaleY, 0.0f));
	
	Vec3 playerScreenCoords = projectionMatrix * game->getPlayer()->getPos();

	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_RenderDrawLine(renderer, x,y, playerScreenCoords.x, playerScreenCoords.y);
	
	// render the player
	game->RenderPlayer(0.10f);

	//bullet->re

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	if (event.type == SDL_MOUSEBUTTONDOWN && event.key.repeat == 0) {
		// shoot bullet
		//Matrix4 projectionMatrix = game_->getProjectionMatrix();
		int x,y;
		SDL_GetMouseState(&x, &y);
		bulletPos.x = x;
		bulletPos.y = y;

		// screenCoords to gameCoords
		auto inverseProjectionMatrix = MMath::inverse(game->getProjectionMatrix());
		bulletPos = inverseProjectionMatrix * bulletPos;

		Vec3 playerScreenCoords = projectionMatrix * game->getPlayer()->getPos();

		Vec3 dir(x-playerScreenCoords.x, y-playerScreenCoords.y,0);
		bullet->setPos(bulletPos);
		//bullet->vel = Vec3();
		bullet->vel = VMath::normalize(dir) * 0.2;

	}
}
