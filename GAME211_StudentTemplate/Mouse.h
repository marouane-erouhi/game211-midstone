#pragma once
struct Mouse{
	float x;
	float y;
	bool leftButtonDown;
	bool rightButtonDown;

	Vec3 getGameCoords(GameManager* game) {
		Vec3 mouseGameCoords = Vec3(x,y,0.0f);
		mouseGameCoords = MMath::inverse(game->getProjectionMatrix()) * mouseGameCoords;
		return mouseGameCoords;
	}

	void update(const SDL_Event& event) {
		///mouse movement
		if (event.type == SDL_MOUSEMOTION) {
			x = event.motion.x;
			y = event.motion.y;
		}

		/// Mouse buttons
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			/// left button
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftButtonDown = true;
			}
			/// right button
			if (event.button.button == SDL_BUTTON_RIGHT) {
				rightButtonDown = true;
			}
			//cout << "click" << endl;
		}
		else {
			leftButtonDown = false;
			rightButtonDown = false;
		}
	}
};