#include "collisions.hpp"

namespace collisions {

	bool pointToRect(SDL_Point point, SDL_Rect rect) { // detects if a SDL Point it's inside a SDL Rect

		bool a = point.x >= rect.x;
		bool b = point.x <= rect.x + rect.w;
		bool c = point.y >= rect.y;
		bool d = point.y <= rect.y + rect.h;

		return a && b && c && d;

	}

	/*bool rectToRect(SDL_Rect rect1, SDL_Rect rect2) { // detects if one of the four corner points of a SDL Rect(1) it's inside a SDL Rect(2)

		bool a = pointToRect(SDL_Point{ rect1.x,rect1.y }, rect2);
		bool b = pointToRect(SDL_Point{ rect1.x,rect1.y + rect1.h }, rect2);
		bool c = pointToRect(SDL_Point{ rect1.x + rect1.w,rect1.y }, rect2);
		bool d = pointToRect(SDL_Point{ rect1.x + rect1.w ,rect1.y + rect1.h }, rect2);

		return a || b || c || d;
	}*/

	bool rectToRect(SDL_Rect rect1, SDL_Rect rect2) { // detects if one of the four corner points of a SDL Rect(1) it's inside a SDL Rect(2)

		bool a = pointToRect(SDL_Point{ rect1.x + 1, rect1.y + 1}, rect2);
		bool b = pointToRect(SDL_Point{ rect1.x + 1, rect1.y + rect1.h - 1}, rect2);
		bool c = pointToRect(SDL_Point{ rect1.x + rect1.w-1, rect1.y +1}, rect2);
		bool d = pointToRect(SDL_Point{ rect1.x + rect1.w -1, rect1.y + rect1.h -1}, rect2);

		return a || b || c || d;
	}

	bool doubleRectToRect(SDL_Rect rect1, SDL_Rect rect2) { // detects if the two SDL Rects are colliding


		bool a = rectToRect(rect1, rect2);
		bool b = rectToRect(rect2, rect1);

		return a || b;

	}

};