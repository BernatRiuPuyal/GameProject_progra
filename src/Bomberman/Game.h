#pragma once
#include "Scene.h"



class Game
{
	//ATRIBUTS
public:

	Scene *currentSc;	//apunta a la escena en curso

private:

	bool isMusicOn;

	state oldState;		//para el control de escenas

	//METODES
public:

	Game();

	~Game();

	void loop();

};

