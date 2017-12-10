#include "Player.h"
#include "Bomb.h"
#include "Constants.h"
#include "Types.h"
#include "collisions.hpp"



Player::Player(colorPJ pj, int x, int y)
{
	player = pj;		//identifica al player segons el seu color 
	lives = 3;
	score = 0;

	pos = { x * SCRIPT_SIZE, y *  SCRIPT_SIZE + HUD_HEIGHT };	//transforma la coordenada del map en pixels
	initial = pos;												//guarda pos inicial, es tornara aqui en cas de morir
	
	invencible = false;
	bombActive = false;

	poweredVelocity = INITIAL_VELOCITY * PU_MULTIPLIER;  //la velocitat amb el power up es igual a la base per 1.8
	velocity = INITIAL_VELOCITY;

	rect = SDL_Rect{ SCRIPT_SIZE, SCRIPT_SIZE * 2, SCRIPT_SIZE, SCRIPT_SIZE };			
	if (player == WHITE) Renderer::Instance()->LoadTexture(PLAYER_W_SPRITE, PATH_IMG + "player1.png");	//si player es white, primer full d'scripts
	else				 Renderer::Instance()->LoadTexture(PLAYER_R_SPRITE, PATH_IMG + "player2.png");	//si no segon
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
	sprite = SDL_Rect{ pos.x, pos.y, SCRIPT_SIZE, SCRIPT_SIZE };	//actualitza on s'imprimeix el pj segons la seva pos

	//Control del temps
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timeDown += deltaTime;			//temps general
	timePowerUp += deltaTime;		//temps dels power up (0 quan s'agafa un)

	//Control dels power ups
	if (timePowerUp <= POWERUP_TIME && type == SKATES) velocity = poweredVelocity;	//mentre estigui en temps i sigui de tipus Skates, velocitat augmentada.
	if (timePowerUp > POWERUP_TIME)													//al terminar temps, velocitat torna a la base i el type a buit, vingui de ser SKATES o HELMET
	{
		type = NOTHING;
		velocity = INITIAL_VELOCITY;
	}

	//Mostra del inventari per consola
	if (player == WHITE) std::cout << "WHITE: ";
	else			     std::cout << "RED:   ";

	if (type == HELMET) std::cout << "HELMET" << std::endl;
	else if (type == SKATES)  std::cout << "SKATES" << std::endl;
	else  std::cout << "NOTHING" << std::endl;
	
}

void Player::putInCenter()		//Centra al PJ en la casella amb la que més espai comparteix
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

void Player::colision(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])	//Diu si el jugador col.lisiona amb un Wall o un Power Up
{
	for (int i = 0; i < 15; i++)		
		for (int j = 0; j < 13; j++)
			if (map[i][j] != nullptr)												//Recorre tot el mapa, si la posició es ocupada i...
				if (collisions::doubleRectToRect(sprite, map[i][j]->sprite))		//... coincideix amb el rect del jugador
				{
					if (map[i][j]->blocksPJ)										//El jugador es centra a la casella d'on ve si es un wall
						putInCenter();
					else if (map[i][j]->type != NOTHING) //pikeable??				//El jugador adopta el tipus del objecte si es un power up...
					{
						type = map[i][j]->type;
						timePowerUp = 0.0;

						map[i][j]->picked = true;									//... i l'envia la senyal per destruirlo.
					}
				}
}

void Player::spawnBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE])		//Col.loca una bomba al map de GameObjects
{
	putInCenter();									//centra al jugador
	whereBomb.x = pos.x / SCRIPT_SIZE;				//es dona a la bomba la posició del jugador (centrada i dividida entre el tamany de cada casella fentla,
	whereBomb.y = pos.y /  SCRIPT_SIZE - 1;														// doncs, coincident amb la posició de la casella del mapa)

	bombActive = true;								//s'activa el bool que indica que el jugador te una bomba en joc

	//Temps, tindrá la funció de controlar la vida de la bomba 
	lastTime = clock();
	timeDown = 0;									//el temps es reinicia

	map[whereBomb.x][whereBomb.y] = new Bomb(player, whereBomb.x, whereBomb.y);	//s'inicialitza la bomba a la casella corresponent a la posició del jugador
}

void Player::myBomb(GameObject *map[SCREEN_WIDTH / SCRIPT_SIZE][(SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE], Player* other, float time)
{

	if (timeDown > 3.0 && timeDown < 4)	//la bomba explota als 3 s i "fa mal" fins als 4
	{
		
		for (int i = 0; i < 9; i++)			//Per cada parcela del rang de l'explosio
		{
			//Comproba si l'explosio toca a cap objecte del mapa
			for (int j = 1; j < SCREEN_WIDTH / SCRIPT_SIZE - 1; j++)
				for (int k = 1; k < (SCREEN_HEIGHT - HUD_HEIGHT) / SCRIPT_SIZE - 1; k++)
					if (map[j][k] != nullptr) {

						if (collisions::doubleRectToRect(map[this->whereBomb.x][this->whereBomb.y]->list[i], map[j][k]->sprite)   //col.lisionen i...
							&& map[j][k]->blocksPJ 																				  //...l'objecte amb que col.lisiona bloqueja al PJ i...
							&& map[j][k]->destructible)																			  //... l'objecte es destruible (es a dir, un wall destruible)
						{
							map[j][k]->impacted = true;		//senyal per a que el wall es destrueixi
							score = score + POINTS_WALL;				//suma al jugador els punts
						}
					}
			//Si la bomba impacta en el mateix jugador que la invoca
			if (collisions::doubleRectToRect(map[this->whereBomb.x][this->whereBomb.y]->list[i], sprite) && !invencible)
			{
				if (type==HELMET)	type = NOTHING;		//si te HELMET, sel treu
				else				lives--;			//si no, li treu vida

				pos = initial;							//"mor" i respawneja a la pos inicial
				invencible = true;						//no pot tornar a patir mal fins que la vida d'aquesta bomba termini
			}
			//Si la bomba impacta en el rival, mateix comportament pero cap al altre jugador...
			if (collisions::doubleRectToRect(map[this->whereBomb.x][this->whereBomb.y]->list[i], other->sprite) && !other->invencible)
			{
				score = score + POINTS_PJ;								//... i es sumen punts al jugador que invoca la bomba.

				if (other->type == HELMET)	other->type = NOTHING;
				else						other->lives--;

				other->pos = other->initial;
				other->invencible = true;
			}
		}
	}
	else if (timeDown >= 4) //als 4 s s'extingueix la bomba i es crida al destructor.
	{
		bombActive = false;											//el jugador deixa de tenir cap bomba activa
		invencible = false;											//els jugadors perden la seva invencibilitat
		other->invencible = false;									
		map[this->whereBomb.x][this->whereBomb.y]->impacted = true;	//fa que la bomba cridi al constructor desde el seu update
	}
}