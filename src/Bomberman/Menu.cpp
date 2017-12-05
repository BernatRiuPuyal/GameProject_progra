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


	list[0] = &buttonPlay;
	list[1] = &buttonRanking;
	list[2] = &buttonQuit;
	list[3] = &buttonSound;



	buttonPlay.pos = SDL_Rect{ 350, 100, 200, 200 };
	buttonRanking.pos = SDL_Rect{ 350, 300, 200, 200 };
	buttonQuit.pos = SDL_Rect{ 350, 400, 200, 200 };
	buttonSound.pos = SDL_Rect{ 350, 500, 200, 200 };

	buttonPlay.text = "Level";
	buttonRanking.text = "Ranking";
	buttonQuit.text = "Quit Game";
	buttonSound.text = "Mute music";

	buttonPlay._state = PLAY;
	buttonRanking._state = GOTORANKING;
	buttonQuit._state = QUIT;
	buttonSound._state = TURNMUSIC;

	const std::string* ids[buttonNum] = { &MENU_TEXT_BUTTON_PLAY,&MENU_TEXT_BUTTON_RANKING,&MENU_TEXT_BUTTON_EXIT, &MENU_TEXT_BUTTON_SOUND };

	for (int i = 0; i < buttonNum; i++) {

		Text textIns;

		textIns.id = *ids[i];
		textIns.text = list[i]->text;
		textIns.color = Color{ 0, 0, 0, 0 };
		Renderer::Instance()->LoadTextureText(font.id, textIns);
	}



	// en teoria aix ja no es necessita
	/*Text textL1;
	textL1.id = "MENU_TEXT_BUTTON_PLAY1"; //perque no deixa usar la constant?
	textL1.text = "Level A";
	textL1.color = Color{ 0, 0, 0, 0 };
	Renderer::Instance()->LoadTextureText(font.id, textL1);
	buttonPlay = SDL_Rect{ 350, 100, 200, 200 };					//PUESTO AL TUNTUN, ARREGLAR aqui y en el resto

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
	buttonSound = SDL_Rect{ 350, 500, 200, 200 };*/


	

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
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_PLAY1", buttonPlay.pos);

	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_RANKING", buttonRanking.pos);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_EXIT", buttonQuit.pos);
	Renderer::Instance()->PushImage("MENU_TEXT_BUTTON_SOUND", buttonSound.pos);



	Renderer::Instance()->Render();
}

void Menu::update()
{
	
	inputHandler();


	

}

void Menu::inputHandler()
{
	
	while (SDL_PollEvent(&event)) {

		switch (event.type) {


		case SDL_MOUSEBUTTONDOWN:


			for (int i = 0; i < buttonNum; i++) {

				if (collisions::pointToRect({ event.motion.x, event.motion.y }, list[i]->pos))
					estado = list[i]->_state;
			}


			
		}

		
	}


}
