#include "Menu.h"
#include "Constants.h"
#include <SDL.h>
#include <iostream>
#include <string>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>


Menu::Menu()
{
	Font font;
	font.id = SAIYAN_80;
	font.path = PATH_FONT + "saiyan.ttf";
	font.size = 80;
	Renderer::Instance()->LoadFont(font);

	Text textL1;
	textL1.id = "MENU_TEXT_BUTTON_PLAY1"; //perque no deixa usar la constant?
	textL1.text = "Level 1";
	textL1.color = Color{ 0, 0, 0, 0 };
	Renderer::Instance()->LoadTextureText(font.id, textL1);
	buttonL1 = SDL_Rect{ 350, 100, 200, 200 };					//PUESTO AL TUNTUN, ARREGLAR aqui y en el resto

	Text textL2;
	textL2.id = "MENU_TEXT_BUTTON_PLAY2"; //perque no deixa usar la constant?
	textL2.text = "Level 2";
	textL2.color = Color{ 0, 0, 0, 0 };
	Renderer::Instance()->LoadTextureText(font.id, textL2);
	buttonL2 = SDL_Rect{ 350, 200, 200, 200 };

	Text textRanking;
	textRanking.id = "MENU_TEXT_BUTTON_RANKING"; //perque no deixa usar la constant?
	textRanking.text = "Ranking";
	textRanking.color = Color{ 0, 0, 0, 0 };
	Renderer::Instance()->LoadTextureText(font.id, textRanking);
	buttonRanking = SDL_Rect{ 350, 300, 200, 200 };
	
	Text textQuit;
	textQuit.id = "MENU_TEXT_BUTTON_EXIT"; //perque no deixa usar la constant?
	textQuit.text = "Quit Game";
	textQuit.color = Color{ 0, 0, 0, 0 };
	Renderer::Instance()->LoadTextureText(font.id, textQuit);
	buttonQuit = SDL_Rect{ 350, 400, 200, 200 };

	Text textSound;
	textSound.id = "MENU_TEXT_BUTTON_SOUND"; //perque no deixa usar la constant?
	textSound.text = "Mute music";
	textSound.color = Color{ 0, 0, 0, 0 };
	Renderer::Instance()->LoadTextureText(font.id, textSound);
	buttonSound = SDL_Rect{ 350, 500, 200, 200 };


}


Menu::~Menu()
{
}

void Menu::setup()
{

}

void Menu::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(MENU_BG, background);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_PLAY1", buttonL1);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_PLAY2", buttonL2);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_RANKING", buttonRanking);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_QUIT", buttonQuit);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_SOUND", buttonSound);
	Renderer::Instance()->Render();
}

void Menu::update()
{

}

void Menu::inputHandler()
{

}
