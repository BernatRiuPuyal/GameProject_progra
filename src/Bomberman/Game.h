#pragma once
#include "Scene.h"

//enum runningSt { MENU, RANKING, PLAY1, PLAY2, QUIT }; //JUNTAR CON EL STATE, CAMBIAR NOMBRE

class Game
{
	//ATR
public:

	int score;

	bool isMusicOn;

	int name;  //nose perque es pero esta al disseny

	//static Game* _game;

private:

	//runningSt currentSt;
	Scene *currentSc;


	//MET
private:
	


public:
	Game();

	~Game();

	/*static Game* instance() { //retorna el punter a l'unic game que pot existir

		if (_game == nullptr) { _game = new Game; }
		return _game;


	};*/
	
	void loop();
};

