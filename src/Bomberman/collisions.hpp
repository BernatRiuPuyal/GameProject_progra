#pragma once
#include <SDL.h>


namespace collisions {

	bool pointToRect(SDL_Point point, SDL_Rect rect);
	bool rectToRect(SDL_Rect rect1, SDL_Rect rect2);
	bool doubleRectToRect(SDL_Rect rect1, SDL_Rect rect2);

};
