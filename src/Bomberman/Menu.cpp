#include "Menu.h"
#include "Constants.h"
#include <SDL.h>
#include <iostream>
#include <string>		
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>
#include "collisions.hpp"


Menu::Menu()
{
	this->estado = INMENU;	//actualitza id d'estat

	list[0] = &buttonPlay1;	//s'allotjen botons a l'array
	list[1] = &buttonPlay2;
	list[2] = &buttonRanking;
	list[3] = &buttonQuit;
	list[4] = &buttonSound;

	//Es defineixen els botons
							
									//tamany i posició
	buttonPlay1.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 100, 150, 200, 100 };
	buttonPlay2.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 100, 250, 200, 100 };
	buttonRanking.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 100, 350, 200, 100 };
	buttonQuit.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 100, 450, 200, 100 };
	buttonSound.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 100, 550, 200, 100 };

									//text
	buttonPlay1.text = "LevelA";
	buttonPlay2.text = "LevelB";
	buttonRanking.text = "Ranking";
	buttonQuit.text = "Quit Game";
	buttonSound.text = "Mute music";

									//cap a on portará
	buttonPlay1._state = PLAY1;
	buttonPlay2._state = PLAY2;
	buttonRanking._state = RANKING;
	buttonQuit._state = QUIT;
	buttonSound._state = TURNMUSIC;

									//id, font i color
	const std::string ids[buttonNum] = { MENU_TEXT_BUTTON_PLAY1, MENU_TEXT_BUTTON_PLAY2, MENU_TEXT_BUTTON_RANKING, MENU_TEXT_BUTTON_EXIT, MENU_TEXT_BUTTON_SOUND };

	for (int i = 0; i < buttonNum; i++) {

		Text textIns;

		textIns.id = ids[i];
		textIns.text = list[i]->text;
		textIns.color = Color{ 0, 0, 0, 0 };
		Renderer::Instance()->LoadTextureText(font.id, textIns);
	}

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
	Renderer::Instance()->PushImage(BG, background);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY1, buttonPlay1.pos);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY2, buttonPlay2.pos);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_RANKING, buttonRanking.pos);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_EXIT, buttonQuit.pos);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_SOUND, buttonSound.pos);
	Renderer::Instance()->Render();
}

void Menu::inputHandler()
{
	while (SDL_PollEvent(&evento)) {

		switch (evento.type) {


		case SDL_MOUSEBUTTONDOWN:

			for (int i = 0; i < buttonNum; i++) {

				if (collisions::pointToRect({ evento.motion.x, evento.motion.y }, list[i]->pos)) {	//detecta si s'ha clickat a un boto
					estado = list[i]->_state;
				}
			}

			break;

		case SDL_QUIT:
			estado = state::QUIT;
			break;
		}

	}
}

void Menu::update()
{
	inputHandler();
}
