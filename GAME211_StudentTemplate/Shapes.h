#pragma once
#include "VMath.h"
#include <SDL.h>
#include "UtilityFunctions.h"

class Shapes {
public:
    ///Source: https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
    static void DrawCircle(GameManager* game, MATH::Vec3 pos, float radius_screen){
        SDL_Renderer* renderer = game->getRenderer();
        const int32_t diameter = int32_t(radius_screen * 2);

        int32_t x = (radius_screen - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        pos = GameToScreenCoords(pos, game);

        while (x >= y)
        {
            // Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, pos.x + x, pos.y - y);
            SDL_RenderDrawPoint(renderer, pos.x + x, pos.y + y);
            SDL_RenderDrawPoint(renderer, pos.x - x, pos.y - y);
            SDL_RenderDrawPoint(renderer, pos.x - x, pos.y + y);
            SDL_RenderDrawPoint(renderer, pos.x + y, pos.y - x);
            SDL_RenderDrawPoint(renderer, pos.x + y, pos.y + x);
            SDL_RenderDrawPoint(renderer, pos.x - y, pos.y - x);
            SDL_RenderDrawPoint(renderer, pos.x - y, pos.y + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
};