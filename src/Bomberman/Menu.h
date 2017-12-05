#pragma once
#include "Scene.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>

struct button {

	SDL_Rect pos;
	std::string text;

	state _state;
};

class Menu :
	public Scene
{
public:
	//ATR
	button buttonPlay;
	button buttonRanking;
	button buttonQuit;
	button buttonSound;

private:
	static const int buttonNum = 4;
	button* list[buttonNum];
public:
	//FNC
	Menu();
	~Menu();

//private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;
};

