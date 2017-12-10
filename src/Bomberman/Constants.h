#pragma once

#define SCREEN_FPS 60.0f
#define SCREEN_TICKS_PER_FRAME (1.0f / SCREEN_FPS)

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 704

#define SCRIPT_SIZE 48
#define HUD_HEIGHT 80

#define INITIAL_VELOCITY 5.0

#define POWERUP_TIME 10
#define PU_MULTIPLIER 1.8 //per quant es multiplica la velocitat amb el power up

#define POINTS_WALL 15
#define POINTS_PJ 100

const std::string BG = "BG";
const std::string EXPLOSION = "EXPLOSION";
const std::string PLAYER_W_SPRITE = "PLAYER_B_SPRITE";
const std::string PLAYER_R_SPRITE = "PLAYER_R_SPRITE";
const std::string ITEM = "ITEM";
const std::string PLAY_TEXT_SCORE_PLAYER1 = "PLAY_TEXT_SCORE_PLAYER1";
const std::string MENU_TEXT_BUTTON_PLAY1 = "MENU_TEXT_BUTTON_PLAY1";
const std::string MENU_TEXT_BUTTON_PLAY2 = "MENU_TEXT_BUTTON_PLAY2";
const std::string MENU_TEXT_BUTTON_EXIT = "MENU_TEXT_BUTTON_EXIT";
const std::string MENU_TEXT_BUTTON_RANKING = "MENU_TEXT_BUTTON_RANKING";
const std::string MENU_TEXT_BUTTON_SOUND = "MENU_TEXT_BUTTON_SOUND";

const std::string LIVES_W = "LIVES_W";
const std::string LIVES_R = "LIVES_R";
const std::string POINTS_W = "POINTS_W";
const std::string POINTS_R = "POINTS_R";
const std::string TIME_COUNT = "TIME_COUNT";

const std::string PATH_IMG = "../../res/img/";
const std::string PATH_FONT = "../../res/ttf/";
const std::string PATH_AU = "../../res/au/";

const std::string SAIYAN_80 = "SAIYAN_80";
const std::string GO_40 = "GO_40";