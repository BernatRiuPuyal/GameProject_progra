#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <time.h>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

int main(int, char*[]) {

	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_FLAC };
	if ( !(Mix_Init(mixFlags) & mixFlags)) throw "laputa";

	if (TTF_Init() != 0) throw "no es pot inicialitzar el ttf";

	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";


	

	

	// --- SPRITES ---

	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bg.jpg") }; // agafa la imatge xd

	if (bgTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../res/img/kintoun.png") };	//Player

	//if (playerTexture == nullptr) throw "No s'han pogut crear les textures";
	//SDL_Rect playerRect{ 0, 0, 350, 189 };

	SDL_Rect playerTarget{ 0,0,100,100 };

		// --- Animated Sprite ---

	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../res/img/sp01.png") };
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 6;
	frameHeight = textHeight / 1;

	playerPosition.x = playerPosition.y = 0;

	playerRect.x = playerRect.y = 0;

	playerPosition.h = playerRect.h = frameHeight;

	playerPosition.w = playerRect.w = frameWidth;

	int frameTime = 0;








	// --- TEXT ---

	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };

	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,"My First SDL Game",SDL_Color{255,150,0,255}) };

	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer,tmpSurf) };

	SDL_Rect textRect{ 100,50,tmpSurf->w,tmpSurf->h };

	SDL_FreeSurface(tmpSurf);

	TTF_CloseFont(font);

	// --- AUDIO ---

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "unable to initialize sdl mixer i tu";

	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };

	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

	Mix_PlayMusic(soundtrack, -1); //-1 = loop infinit de musica

	//MIX_



	//--TIME--

	clock_t lastTime = clock();

	float timedown = 10;
	float deltaTime = 0;






	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning){
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		isRunning = false; break;
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
			case SDL_MOUSEMOTION:											//Player2.0
				playerTarget.x = event.motion.x - 50;
				playerTarget.y = event.motion.y - 50;
				break;

			default:;
			}
		}

		// UPDATE



		frameTime++;

		if (FPS / frameTime <= 9)
		{

			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textWidth)
				playerRect.x = 0;



		}

		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timedown -= deltaTime;







		// DRAW
			//Background
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect); // background

		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		



			//Animated Sprite
		SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
		//SDL
		






		SDL_RenderPresent(renderer);

		


	}

	// --- DESTROY ---
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_DestroyTexture(textTexture);

	// --- QUIT ---

	Mix_CloseAudio();

	Mix_Quit();
	SDL_Quit();
	return 0;


#pragma region "satanas"


	// yow
#pragma endregion
}