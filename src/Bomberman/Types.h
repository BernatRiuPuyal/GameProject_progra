#pragma once
#include <string>
#include <SDL.h>

	using Rect = struct  Rect{ int  x; int y; int w; int h; };

	using Color = struct Color { Uint8 r; Uint8 g; Uint8 b; Uint8 a; };
	
	struct Vector2 { int x; int y; };

	using Font = struct {
		std::string id;
		std::string path;
		int size;
	};

	using Text = struct {
		std::string id;
		std::string text;
		Color color;
		int w;
		int h;
	};

	enum class Key {UP, DOWN, LEFT, RIGHT, NONE};

	enum colorPJ { WHITE, RED };

	enum powerUp { SKATES, HELMET, NOTHING };

	enum state { INMENU, TOMENU, RANKING, PLAY1, PLAY2, QUIT, TURNMUSIC }; //INMENU per al primer menu, TOMENU quan es torna al menu des d'un altre escena

	struct number {

		SDL_Rect pos;
		std::string text;

	};

	struct button {

		SDL_Rect pos;
		std::string text;

		state _state;
	};

	struct position { int x;  int y; };