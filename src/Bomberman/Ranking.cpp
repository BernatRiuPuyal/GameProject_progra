#include "Ranking.h"
#include <fstream> // necessari pel ifstream
#include <algorithm>
#include <string>


Ranking::Ranking(bool comeFromLevel, int _maxScore, int pjID)
{
	fromLevel = comeFromLevel;
	maxScore = _maxScore;

	// read Ranking

	//rank.resize(10);
	this->estado = RANKING;

	std::ifstream fentrada("../../res/files/ranking.bin", std::ios::in | std::ios::binary);

	if (fentrada) { //comprova si existeix




		for (int i = 0; i < PLAYERS_ON_RANKING; i++) { //encara he provat res del binari

			size_t length;
			std::string name;
			int score;


			fentrada.read(reinterpret_cast<char*>(&length), sizeof(size_t)); // llegeix la longitud del array

			char *temp = new char[length + 1]; //crea auxiliar que guardarà el nom

			fentrada.read(temp, length);

			temp[length] = '\0';

			name = temp;

			delete[] temp;

			fentrada.read(reinterpret_cast<char*>(&score), sizeof(score));

			rank.push_back({ name,score });

		}

		fentrada.close();

	}
	else { // sino existeix omple el vector amb "Empty Slots" - es guardara en un nou ranking.bin
		for (int i = 0; i < 10; i++)
		rank.push_back( { "Empty Slot", 0 });
		

	}

	//create button

	buttonBack.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 75, 580, 150, 66 };
	buttonBack.text = "Back";
	buttonBack._state = state::TOMENU;

	Renderer::Instance()->LoadTextureText(font.id,  { RANKING_TEXT_BACK,"BACK",Color{0,0,0,0} });
	if(pjID == 0)		Renderer::Instance()->LoadTextureText(font2.id, { "PLAYER1_ENTER_NAME","WINS 1, WRITE YOUR NAME:",Color{0,0,0,0} });
	else if(pjID == 1)  Renderer::Instance()->LoadTextureText(font2.id, { "PLAYER1_ENTER_NAME","WINS 2, WRITE YOUR NAME:",Color{ 0,0,0,0 } });
	
	


	//Carrega textures amb les dades del vector
	
	loadRank();

	_phase = (comeFromLevel) ? ENTERNAME : SHOWRANK; // determina que es mostrarà per començar

}


Ranking::~Ranking()
{
	//save ranking

	std::ofstream fentrada("../../res/files/ranking.bin", std::ios::out | std::ios::binary);


	for (int i = 0; i < PLAYERS_ON_RANKING; i++) {

		
		std::string name= rank[i].name;
		size_t length = name.size();
		int score = rank[i].score;


		fentrada.write(reinterpret_cast<char*>(length), sizeof(size_t)); // escriu la longitud del array
				
		fentrada.write(name.c_str(), length); // escriu array


		fentrada.write(reinterpret_cast<char*>(&score), sizeof(score)); //escriu score

		
	}

	fentrada.close();

}

void Ranking::setup()
{
	

}

void Ranking::draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage(BG, background);
	
	switch (_phase)
	{
	case Ranking::ENTERNAME:

		Renderer::Instance()->PushImage("PLAYER1_ENTER_NAME", { SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 40,500,80 });

		break;

	case Ranking::SHOWRANK:

		for (int i = 0; i < 10; i++)
			Renderer::Instance()->PushImage("PJ" + std::to_string(i+1), { SCREEN_WIDTH / 2 - 150, HUD_HEIGHT + SCRIPT_SIZE + 40 * i, 300, 40 });
		
		Renderer::Instance()->PushImage(RANKING_TEXT_BACK, buttonBack.pos);

		break;

	}


	Renderer::Instance()->Render();



	}


void Ranking::update() 
{
	if (_phase == ENTERNAME) {
	
		std::string introName;
		std::cin >> introName;

		rank.push_back({ introName, maxScore });
		//sort de rank
		std::sort(rank.begin(),rank.end());
		std::reverse(rank.begin(), rank.end());
		rank.pop_back();

		loadRank();

		_phase = SHOWRANK;
	}
}

void Ranking::inputHandler()
{
	while (SDL_PollEvent(&evento)) {

		switch (evento.type) {


		case SDL_MOUSEBUTTONDOWN:
			
			if (collisions::pointToRect({ evento.motion.x, evento.motion.y }, buttonBack.pos))	{//detecta si s'ha clickat a un boto
				
				
				
				//save ranking

				std::ofstream fentrada("../../res/files/ranking.bin", std::ios::out | std::ios::binary);


				for (int i = 0; i < PLAYERS_ON_RANKING; i++) {


					std::string name = rank[i].name;
					size_t length = name.size();
					int score = rank[i].score;


					fentrada.write(reinterpret_cast<char*>(&length), sizeof(size_t)); // escriu la longitud del array				
					

					fentrada.write(name.c_str(), name.size()); // escriu array

					fentrada.write(reinterpret_cast<char*>(&score), sizeof(score)); //escriu score
				

			}

			fentrada.close();
				
				
								
				
				estado = buttonBack._state;
			}
			break;

		case SDL_QUIT:
			estado = state::QUIT;
			break;

		}
	}
}

void Ranking::loadRank()
{
	for (int i = 0; i < 10; i++)
		Renderer::Instance()->LoadTextureText(font3.id, { "PJ" + std::to_string(i + 1), rank[i].name + " - " + std::to_string(rank[i].score), Color{ 0,0,0,0 } });
}
