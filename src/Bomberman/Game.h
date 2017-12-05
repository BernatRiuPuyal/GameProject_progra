#pragma once


class Game // usat per guardar les variables globals
{

	// atributos

public:

	int score;

	bool isMusicOn;

	int name;  //nose perque es pero esta al disseny

	static Game* _game;



	//metodos


private:
	Game();

public:
	~Game();



	static Game* instance() { //retorna el punter a l'unic game que pot existir

		if (_game == nullptr) { _game = new Game; }
		return _game;


	};






};

