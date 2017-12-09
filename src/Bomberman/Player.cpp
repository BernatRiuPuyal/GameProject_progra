#include "Player.h"
#include "Bomb.h"
#include "Constants.h"
#include "Types.h"
#include "collisions.hpp"

Player::Player(colorPJ pj, int x, int y)
{
	player = pj;
	pos = { x, y };

	pos.x = pos.x * SCRIPT_SIZE;
	pos.y = pos.y *  SCRIPT_SIZE + HUD_HEIGHT;

	initial = pos;

	invencible = false;

	initialVelocity = 5.0;
	poweredVelocity = initialVelocity * 1.8;
	velocity = initialVelocity;

	lives = 3;

	score = 0;

	bombActive = false;

	rect = SDL_Rect{ SCRIPT_SIZE, SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };

	if (player == WHITE) Renderer::Instance()->LoadTexture(PLAYER_W_SPRITE, PATH_IMG + "player1.png");
	else				Renderer::Instance()->LoadTexture(PLAYER_R_SPRITE, PATH_IMG + "player2.png");

}

Player::~Player()
{

}

void Player::setup()
{

}

void Player::draw()
{
	if (player == WHITE)Renderer::Instance()->PushSprite(PLAYER_W_SPRITE, rect, sprite);
	else				Renderer::Instance()->PushSprite(PLAYER_R_SPRITE, rect, sprite);
}

void Player::update(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])
{	
	sprite = SDL_Rect{ pos.x, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };

	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown += deltaTime;
	timeSkates += deltaTime;
	timeHelmet += deltaTime;

	if (timeSkates < 10 && type == SKATES) velocity = poweredVelocity;
	else 
	{
		velocity = initialVelocity;
		type == NOTHING;
	}

	if (timeHelmet > 10 || type == !HELMET) type == NOTHING;
}

void Player::inputHandler()
{
}

void Player::putInCenter()
{
	int x, y;
	float X, Y;


	x = pos.x / (SCRIPT_SIZE / 2);
	y = (pos.y - HUD_HEIGHT) / (SCRIPT_SIZE / 2);

	X = (float)x / 2;
	Y = (float)y / 2;
	x = x / 2;
	y = y / 2;

	if(X > x)	pos.x = (x + 1) * SCRIPT_SIZE;
	else		pos.x = x * SCRIPT_SIZE;

	if (Y > y)	pos.y = (y + 1) * SCRIPT_SIZE + 80;
	else		pos.y = y * SCRIPT_SIZE + 80;
}

void Player::colision(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])
{
	for (int i = 0; i < 15; i++)
		//{
		for (int j = 0; j < 13; j++)
			if (map[i][j] != nullptr)
				if (collisions::doubleRectToRect(sprite, map[i][j]->sprite))
				{
					if (map[i][j]->blocksPJ)
						putInCenter();
					else if (map[i][j]->type != NOTHING)
					{
						type = map[i][j]->type;

						if (map[i][j]->type == HELMET) timeHelmet = 0.0;
						else timeSkates = 0.0;

						map[i][j]->picked = true;
					}
				}

}

void Player::spawnBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])
{

	putInCenter();
	whereBomb.x = pos.x / SCRIPT_SIZE;
	whereBomb.y = pos.y /  SCRIPT_SIZE - 1;

	bombActive = true;
	//time
	lastTime = clock();
	timeDown = 0;

	map[whereBomb.x][whereBomb.y] = new Bomb(player, whereBomb.x, whereBomb.y);
	
}

void Player::myBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE], Player* other, float time)
{

	if (timeDown > 3.0 && timeDown < 4.0)	//Al explotar
	{
		
		for (int i = 0; i < 9; i++)
		{

			//checkeja mapa
			for (int j = 1; j < SCREEN_WIDTH / SCRIPT_SIZE - 1; j++)
			{

				for (int k = 1; k < (SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE - 1; k++)
				{


					if (map[j][k] != nullptr /*&& map[this->whereBomb.x][this->whereBomb.y] != nullptr*/) {

						if (collisions::doubleRectToRect(map[this->whereBomb.x][this->whereBomb.y]->list[i], map[j][k]->sprite) && map[j][k]->blocksPJ && map[j][k]->destructible)
						{
							map[j][k]->impacted = true;
							score = score + 15;
							std::cout << j << " " << k << std::endl;
						}
					}
				}
			}
			//checkeja pj
			if (collisions::doubleRectToRect(map[this->whereBomb.x][this->whereBomb.y]->list[i], sprite) && !invencible)
			{
				if (type==HELMET)	type == NOTHING;
				else				lives--;

				pos = initial;
				invencible = true;
			}
			if (collisions::doubleRectToRect(map[this->whereBomb.x][this->whereBomb.y]->list[i], other->sprite) && !other->invencible)
			{
				score = score + 100;

				if (other->type == HELMET)	other->type == NOTHING;
				else						other->lives--;

				other->pos = other->initial;
				other->invencible = true;
			}
		}

	}
	else if (timeDown > 4.0)
	{
		bombActive = false;
		invencible = false;
		other->invencible = false;
		map[this->whereBomb.x][this->whereBomb.y]->impacted = true;
	}
	std::cout << bombActive << std::endl;
}