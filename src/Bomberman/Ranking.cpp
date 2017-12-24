#include "Ranking.h"
#include <fstream> // necessari pel ifstream
#include <algorithm>
#include <string>


Ranking::Ranking(bool comeFromLevel, int maxScore, int pjID)
{
	fromLevel = comeFromLevel;

	// read Ranking

	//rank.resize(10);
	this->estado = RANKING;

	std::ifstream fentrada("../../res/files/ranking.bin", std::ios::in | std::ios::binary);

	for (int i = 0; i < PLAYERS_ON_RANKING; i++) { //encara he provat res del binari

		size_t length =0;
		std::string name;
		int score;


		fentrada.read(reinterpret_cast<char*>(length), sizeof(size_t)); // llegeix la longitud del array

		char *temp = new char[length + 1]; //crea auxiliar que guardarà el nom

		fentrada.read(reinterpret_cast<char*>(&length), length);

		temp[length] = '\0';

		name = temp;

		delete[] temp;

		fentrada.read(reinterpret_cast<char*>(&score), sizeof(score));

		rank.push_back({ name,score});

	}

	fentrada.close();



	//create button

	buttonBack.pos = SDL_Rect{ SCREEN_WIDTH / 2 - 75, 580, 150, 66 };
	buttonBack.text = "Back";
	buttonBack._state = state::TOMENU;

	Renderer::Instance()->LoadTextureText(font.id,  { RANKING_TEXT_BACK,"BACK",Color{0,0,0,0} });
	if(pjID == 0)		Renderer::Instance()->LoadTextureText(font2.id, { "PLAYER1_ENTER_NAME","WINS 1, WRITE YOUR NAME:",Color{0,0,0,0} });
	else if(pjID == 1)  Renderer::Instance()->LoadTextureText(font2.id, { "PLAYER1_ENTER_NAME","WINS 2, WRITE YOUR NAME:",Color{ 0,0,0,0 } });
	
	
	//////////OMPLE VECTOR A MÀ PER PROVAR!!!!!!!!!!!!!!!!!! ---- Es podria usar com a ranking per defecte del joc???
	//for (int i = 0; i < 10; i++)
	//	rank[i] = { "Jugador" + std::to_string(i + 1), 3000 - 246 * i };
	//////////////////////////////////////////////////////////

	//Carrega textures amb les dades del vector
	for(int i = 0; i < 10; i++)
		Renderer::Instance()->LoadTextureText(font3.id, { "PJ" + std::to_string(i+1), rank[i].name + " - " + std::to_string(rank[i].score), Color{ 0,0,0,0 } });


	enterName = (comeFromLevel) ? ENTERNAME1 : SHOWRANK; // determina que es mostrarà per començar

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
	
	switch (enterName)
	{
	case Ranking::ENTERNAME1:

		Renderer::Instance()->PushImage("PLAYER1_ENTER_NAME", { SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 40,500,80 });

		break;
	case Ranking::ENTERNAME2:

		Renderer::Instance()->PushImage("PLAYER2_ENTER_NAME", { SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 40,500,80 });

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
	if (fromLevel) {
		std::cin >> introName;

		rank.push_back({ introName, maxScore });
		//sort de rank
		rank.resize(10);

		estado = TOMENU;
	}
}

void Ranking::inputHandler()
{
	while (SDL_PollEvent(&evento)) {

		switch (evento.type) {


		case SDL_MOUSEBUTTONDOWN:

			if (collisions::pointToRect({ evento.motion.x, evento.motion.y }, buttonBack.pos))	//detecta si s'ha clickat a un boto
				estado = buttonBack._state;

			break;

		case SDL_QUIT:
			estado = state::QUIT;
			break;

		}
	}
}
