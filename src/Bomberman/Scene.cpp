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
	Renderer::Instance()->LoadTexture(MENU_BG, PATH_IMG + "bg.jpg");
	background = SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}


Scene::~Scene()
{
}
