#pragma once
#include "GameObject.h"
class Bomb :
	public GameObject
{
	//ATRIBUTS
private:
	position coord;	//posició a la casella del mapa

	SDL_Rect rect1, rect2, rect3, rect4, rect5, rect6, rect7;									//Rects per l'explosió
	SDL_Rect sprite1, sprite2, sprite3, sprite4, sprite5, sprite6, sprite7, sprite8, sprite9;	//sprites per l'explosió

public:
	colorPJ idPJ;	//color del PJ que la crea per identificarlo

	//METODES
public:
	Bomb(colorPJ id, int x, int y);
	~Bomb();
	void setup() override;
	void draw() override;
	void update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE]) override;

};

