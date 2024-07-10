#include "Scene1.h"
#include <VMath.h>
#include "ResourceManager.h"
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

	// add the bullet image from file
	bullet = new Bullet(ResourceManager::getInstance()->AddImage(game, "Art/Bullet.png"));

	//SDL_Surface* a = IMG_Load("Art/Bullet.png");
	//bullet->setImage(a);
	//bullet->setTexture(SDL_CreateTextureFromSurface(renderer, a));

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

	if (mouse.leftButtonDown) {
		Vec3 playerScreenCoords = projectionMatrix * game->getPlayer()->getPos();
		auto playerPos = game->getPlayer()->getPos();
		Vec3 m = mouse.getGameCoords(game);

		Vec3 dir(m.x - playerPos.x, m.y - playerPos.y, 0);

		// get the angle for the bullet, dir.y is reversed since up is negetive
		bulletAng = std::atan2(-dir.y, dir.x) * (180.0f / M_PI);

		bullet->setPos(Vec3(m.x,m.y,0.0f));
		//bullet->vel = Vec3();
		bullet->setDir(dir);// speed
	}



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
	bullet->Render(game);
	
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
