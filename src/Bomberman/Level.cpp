#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "Constants.h"
#include "Bomb.h"
#include "PowerUp.h"
#include "collisions.hpp"
#include <time.h>
#include <string> 


#include "PowerUP.h"

Level::Level(LevelConfig _set)
{

	this->estado = PLAY1;

	int auxLives;


	//Neteja memoria
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 13; j++)
			map[i][j] = nullptr;

	switch (_set)
	{
	case DEFAULT:

		this->estado = PLAY1;

		#pragma region anticMuntatge
			
		
			//Omple tot de destruibles
			for (int i = 1; i < 14; i++)
				for (int j = 1; j < 12; j++)
					map[i][j] = new Wall(true, i, j);
		
			//Coloca no destruibles
			for (int i = 2; i <= 12; i = i + 2)
				for (int j = 2; j <= 10; j = j + 2)
					map[i][j] = new Wall(false, i, j);
		

		
			//Neteja els llocs que han de ser buits
			map[1][1] = nullptr;	//Cantonada superior esquerra
			map[1][2] = nullptr;
			map[1][3] = nullptr;
			map[2][1] = nullptr;
			map[3][1] = nullptr;
		
			map[13][11] = nullptr;	//Cantonada inferior dreta
			map[13][10] = nullptr;
			map[13][9]  = nullptr;
			map[12][11] = nullptr;
			map[11][11] = nullptr;
		
		
		#pragma endregion anticMuntatge

			timeDown = 80;		//Segons que durara com a maxim la partida
			auxLives = 3;
		break;
	case LEVEL1:

	{
		rapidxml::xml_document<> doc;

		std::ifstream file("../../res/files/config.xml");

		std::stringstream buffer;

		buffer << file.rdbuf();

		file.close();

		std::string content(buffer.str());

		doc.parse<0>(&content[0]);

		rapidxml::xml_node<> *pRoot = doc.first_node();

		rapidxml::xml_node<> *pLevel = pRoot->first_node("Level");

		while (atoi(pLevel->first_attribute("id")->value()) != static_cast<int>(_set)) { //search Level

			pLevel = pLevel->next_sibling("Level");
		}



		timeDown = atoi(pLevel->first_attribute("time")->value());		//Segons que durara com a maxim la partida

		auxLives = atoi(pLevel->first_attribute("lives")->value());	//vides dels jugadors


		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Destructible")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("i")->value());
			int j = atoi(pWall->first_attribute("j")->value());

			map[j + 1][i + 1] = new Wall(true, j + 1, i + 1);
		}


		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Fixed")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("i")->value());
			int j = atoi(pWall->first_attribute("j")->value());

			map[j + 1][i + 1] = new Wall(false, j + 1, i + 1);
		}
	}

		break;

	case LEVEL2:

	{
		rapidxml::xml_document<> doc;

		std::ifstream file("../../res/files/config.xml");

		std::stringstream buffer;

		buffer << file.rdbuf();

		file.close();

		std::string content(buffer.str());

		doc.parse<0>(&content[0]);

		rapidxml::xml_node<> *pRoot = doc.first_node();

		rapidxml::xml_node<> *pLevel = pRoot->first_node("Level");

		while (atoi(pLevel->first_attribute("id")->value()) != static_cast<int>(_set) ) { //search Level

			pLevel = pLevel->next_sibling("Level");
		}

		

		timeDown = atoi(pLevel->first_attribute("time")->value());		//Segons que durara com a maxim la partida

		auxLives = atoi(pLevel->first_attribute("lives")->value());	//vides dels jugadors


		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Destructible")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("i")->value());
			int j = atoi(pWall->first_attribute("j")->value());

			map[j+1][i+1] = new Wall(true, j+1, i+1);
		}


		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Fixed")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("i")->value());
			int j = atoi(pWall->first_attribute("j")->value());

			map[j+1][i+1] = new Wall(false, j+1, i+1);
		}
	}
	
		break;
	}

	


	//Omple exterior de no destruibles (limits del mapa)
	for (int i = 0; i < 15; i++) map[i][0] = new Wall(false, i, 0);	//y = 0
	for (int i = 0; i < 15; i++) map[i][12] = new Wall(false, i, 12);	//y = 12
	for (int i = 0; i < 13; i++) map[0][i] = new Wall(false, 0, i);	//x = 0
	for (int i = 0; i < 13; i++) map[14][i] = new Wall(false, 14, i);	//x = 14

	
	//Col.loca PJ | algoritme que els coloca al lloc buit més aprop de la seva cantonada
	int i = 1, j = 1;
	int lastLine = 1;
	while (map[i][j] != nullptr) {

		
		if (i == 1) {
			lastLine++;
			i = lastLine;
			j = 1;
		}
		else {
			j++;
			i--;
		}

	}

	
	pj[0] = new Player(WHITE, i, j);

	i = 13;
	j = 11;
	lastLine = 13;

	while (map[i][j] != nullptr) {

		if (i == 13) {
			lastLine--;
			i = lastLine;
			j = 11;
		}
		else {
			j--;
			i++;
		}
	}
	


	pj[1] = new Player(RED, i, j);


	for (int i = 0; i < numPlayers; i++) {
		pj[i]->lives = auxLives;
	}


	//HUD//
				//Icones jugadors
	spriteW = SDL_Rect{ SCRIPT_SIZE*2, (HUD_HEIGHT - SCRIPT_SIZE)/2, SCRIPT_SIZE, SCRIPT_SIZE };					//sprite i posició
	spriteR = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE*3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE, SCRIPT_SIZE };
	rect = SDL_Rect{ SCRIPT_SIZE, SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };										//porció del sprite

				//Vides jugadors
	livesW.pos = SDL_Rect{ SCRIPT_SIZE, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE, SCRIPT_SIZE };
	livesR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE*2, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE, SCRIPT_SIZE };
				
				//Puntuació al update, ja que variará el seu tamany segons el nombre de xifres del valor de la puntuacio

				//Text pels elements del HUD
	textPointsW.color = textPointsR.color = Color{ 0, 255, 0, 0 };	//Points = verds
	textLivesW.color = textLivesR.color = Color{ 255, 0, 0, 0 };	//Vides = vermelles
				//ids
	textPointsW.id = POINTS_W;										
	textPointsR.id = POINTS_R;
	textLivesW.id = LIVES_W;
	textLivesR.id = LIVES_R;

	//Dibuix del clock
	timeCount.pos = SDL_Rect{ SCREEN_HEIGHT / 2 - SCRIPT_SIZE, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE*2, SCRIPT_SIZE };
	
	textTime.color = Color{ 0, 0, 255, 0 };		//Blau
	textTime.id = TIME_COUNT;					//id

	//Variables per controlar el temps
	lastTime = clock();
	
}


Level::~Level()
{

}

void Level::setup() 
{

}

void Level::draw()
{
	Renderer::Instance()->Clear();

	//Background
	Renderer::Instance()->PushImage(BG, background);
	
	//PJs
	for (int i = 0; i < numPlayers; i++)
		pj[i]->draw();

	//MAPA 
	for (int i = 1; i < 14; i++)
		for (int j = 1; j < 12; j++)
			if(map[i][j] != nullptr) map[i][j]->draw();

	//HUD
	Renderer::Instance()->PushSprite(PLAYER_W_SPRITE, rect, spriteW);
	Renderer::Instance()->PushSprite(PLAYER_R_SPRITE, rect, spriteR);
	Renderer::Instance()->PushImage(LIVES_W, livesW.pos);
	Renderer::Instance()->PushImage(LIVES_R, livesR.pos);
	Renderer::Instance()->PushImage(POINTS_W, pointsW.pos);
	Renderer::Instance()->PushImage(POINTS_R, pointsR.pos);
	Renderer::Instance()->PushImage(TIME_COUNT, timeCount.pos);

	Renderer::Instance()->Render();
}

void Level::update()
{
	//Comprova col.lisions dels PJs amb els elements del mapa
	for (int i = 0; i < numPlayers; i++)
		pj[i]->colision(map);

	//Actualitza els PJs
	for (int i = 0; i < numPlayers; i++)
		pj[i]->update(map);

	//Comprova el comportament de les bombes dels PJ
	if (pj[0]->bombActive) pj[0]->myBomb(map, pj[1], timeDown);
	if (pj[1]->bombActive) pj[1]->myBomb(map, pj[0], timeDown);

	//Actualitza els elements del mapa
	for (int i = 1; i < 14; i++)
		for (int j = 1; j < 12; j++)
			if (map[i][j] != nullptr) map[i][j]->update(map);

	//Actualitza el comptador de vides
	textLivesW.text = std::to_string(pj[0]->lives);
	Renderer::Instance()->LoadTextureText(font2.id, textLivesW);
	textLivesR.text = std::to_string(pj[1]->lives);
	Renderer::Instance()->LoadTextureText(font2.id, textLivesR);

	//Actualitza els punts de cada jugador
			//Ajusta el tamany del rect segons les xifres del valor de la puntuació
	if (pj[0]->score < 100 && pj[0]->score > 9)	pointsW.pos = SDL_Rect{ SCRIPT_SIZE * 3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 2, SCRIPT_SIZE };	//DECENES
	else if (pj[0]->score < 10)					pointsW.pos = SDL_Rect{ SCRIPT_SIZE * 3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 1, SCRIPT_SIZE };	//UNITATS
	else										pointsW.pos = SDL_Rect{ SCRIPT_SIZE * 3, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 3, SCRIPT_SIZE };	//CENTENES
		
	if (pj[1]->score < 100 && pj[1]->score > 9)	pointsR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE * 5, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 2, SCRIPT_SIZE };	//DECENES
	else if (pj[1]->score < 10)					pointsR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE * 4, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 1, SCRIPT_SIZE }; 	//UNITATS
	else										pointsR.pos = SDL_Rect{ SCREEN_HEIGHT - SCRIPT_SIZE * 6, (HUD_HEIGHT - SCRIPT_SIZE) / 2, SCRIPT_SIZE * 3, SCRIPT_SIZE };	//CENTENES

	textPointsW.text = std::to_string(pj[0]->score);
	Renderer::Instance()->LoadTextureText(font2.id, textPointsW);
	textPointsR.text = std::to_string(pj[1]->score);
	Renderer::Instance()->LoadTextureText(font2.id, textPointsR);

	//Clock
		//Control del temps
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown -= deltaTime;
		
		//Imprimeix el temps
	textTime.text = std::to_string((int)timeDown);
	Renderer::Instance()->LoadTextureText(font2.id, textTime);

	//FIN DEL JUEGO//

	if (timeDown < 0 || pj[0]->lives <= 0 || pj[1]->lives <= 0) {

		//Determina qui guanya
		if (timeDown < 0) {
			if (pj[0]->score >= pj[1]->score)
			{
				maxScore = pj[0]->score;
				playerID = 0;
			}
			else
			{
				maxScore = pj[1]->score;
				playerID = 1;
			}
		}
		else if (pj[0]->lives <= 0)
		{
			maxScore = pj[1]->score;
			playerID = 1;
		}
		else
		{
			maxScore = pj[0]->score;
			playerID = 0;
		}

		estado = RANKING;
	}
}

void Level::inputHandler()
{
	while (SDL_PollEvent(&evento)) {
		switch (evento.type) {

		case SDL_QUIT:

			estado = QUIT;

			break;

		case SDL_KEYDOWN:
			switch (evento.key.keysym.sym) {

		//PJ WHITE////////////////////////////////////////

			case SDLK_a:

				if (!pj[0]->tHor_fVer) pj[0]->putInCenter();	//Si n'hi ha un canvi de direcció, el PJ es coloca al centre (Per evitar que el jugador hagi de buscar posició exacte per encaixar entre blocs de pedra)
				else pj[0]->pos.x -= pj[0]->velocity;			//Si no, s'aplica velocitat.

				pj[0]->tHor_fVer = true;						//Recull la direcció que ha tomat el PJ (HOR o VERT)

				break;

			case SDLK_d:

				if (!pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.x += pj[0]->velocity;

				pj[0]->tHor_fVer = true;

				break;

			case SDLK_w:

				if (pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.y -= pj[0]->velocity;

				pj[0]->tHor_fVer = false;

				break;

			case SDLK_s:

				if (pj[0]->tHor_fVer) pj[0]->putInCenter();
				else pj[0]->pos.y += pj[0]->velocity;

				pj[0]->tHor_fVer = false;

				break;

			case SDLK_SPACE:

				if(!pj[0]->bombActive) pj[0]->spawnBomb(map);	//Si no n'hi cap bomba activada, spawneja una a la posició en la que es troba

				break;

			//PJ RED////////////////////////////////////////

			case SDLK_LEFT:

				if (!pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.x -= pj[1]->velocity;
				
				pj[1]->tHor_fVer = true;

				break;

			case SDLK_RIGHT:

				if (!pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.x += pj[1]->velocity;
				
				pj[1]->tHor_fVer = true;

				break;

			case SDLK_UP:

				if (pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.y -= pj[1]->velocity;
				
				pj[1]->tHor_fVer = false;

				break;

			case SDLK_DOWN:

				if (pj[1]->tHor_fVer) pj[1]->putInCenter();
				else pj[1]->pos.y += pj[1]->velocity;
				
				pj[1]->tHor_fVer = false;

				break;

			case SDLK_RCTRL:

				if (!pj[1]->bombActive) pj[1]->spawnBomb(map);

				break;

			//////////////////////////////////////////

			default: break;
			}
		}	
	}
}