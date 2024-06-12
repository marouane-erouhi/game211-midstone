#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include "GameManager.h"

// contains all image assets used in game
class ResourceManager {
	std::vector<SDL_Surface*> images;
	std::vector<SDL_Texture*> textures;
	static ResourceManager* instance;

	// Delete copy constructor and assignment operator to prevent copying
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

public:
	ResourceManager();
	static ResourceManager* getInstance();

	int AddImage(GameManager* game_, std::string fileName);
	void RenderImage(GameManager* game_, int i, Vec3 scale_ = Vec3(1.0f, 1.0f, 1.0f), float orientation_ = 0.0f);
};