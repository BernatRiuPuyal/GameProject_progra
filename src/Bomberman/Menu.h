#pragma once
#include "Scene.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>

class Menu :
	public Scene
{
	//ATRIBUTS
private:
	button buttonPlay1;		//botons presents al menu
	button buttonPlay2;
	button buttonRanking;
	button buttonQuit;
	button buttonSound;

	static const int buttonNum = 5;		//array que els allotjara
	button* list[buttonNum];

	//METODES
public:
	Menu();
	~Menu();

private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;
};

