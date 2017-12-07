#include "Player.h"



Player::Player(colorPJ pj, int x, int y)
{
	player = pj;
	pos = { x, y };

	sprite = SDL_Rect{ pos.x * SCRIPT_SIZE, pos.y *  SCRIPT_SIZE + HUD_HEIGHT, SCRIPT_SIZE, SCRIPT_SIZE };

	if (player == BLUE)
	{
		rect = SDL_Rect{ SCRIPT_SIZE, 0, SCRIPT_SIZE, SCRIPT_SIZE };
		Renderer::Instance()->LoadTexture(PLAYER_B, PATH_IMG + "player1.png");
	}
	else 
	{
		rect = SDL_Rect{ 0, 0, SCRIPT_SIZE, SCRIPT_SIZE };
		Renderer::Instance()->LoadTexture(ITEM, PATH_IMG + "player2.png");
	}
}

Player::~Player()
{

}

void Player::setup()
{

}

void Player::draw()
{

}

void Player::update()
{

}

void Player::inputHandler()
{

}