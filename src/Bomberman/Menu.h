#pragma once
#include "Scene.h"
#include "Constants.h"
class Menu :
	public Scene
{
public:
	//ATR
	SDL_Rect buttonL1;
	SDL_Rect buttonL2;
	SDL_Rect buttonRanking;
	SDL_Rect buttonQuit;
	SDL_Rect buttonSound;

	//FNC
	Menu();
	~Menu();

//private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;
};

