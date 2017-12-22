#include "Scene.h"
#include <SDL.h>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"
#include "Constants.h"



Scene::Scene()
{	
	//Background
	background = SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	Renderer::Instance()->LoadTexture(BG, PATH_IMG + "bgGame.jpg");

	//Font 1
	font.id = SAIYAN_80;
	font.path = PATH_FONT + "saiyan.ttf";
	font.size = 80;
	Renderer::Instance()->LoadFont(font);

	//Font 2
	font2.id = GO_40;
	font2.path = PATH_FONT + "game_over.ttf";
	font2.size = 80;
	Renderer::Instance()->LoadFont(font2);

	//font 3

	font3.id = GO_40;
	font3.path = PATH_FONT + "game_over.ttf";
	font3.size = 40;
	Renderer::Instance()->LoadFont(font3);
}


Scene::~Scene()
{
}
