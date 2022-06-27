#ifndef functions_h
#define functions_h

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
////Dimensions of the screen
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

//Dimensions of the level
#define LEVEL_WIDTH     1280
#define LEVEL_HEIGHT    960

//Start position
#define START_X_POS        640
#define START_Y_POS        480
#define START_SCORE_VALUE  0

//Enemy labels
#define ENEMY1 1
#define ENEMY2 2
#define ENEMY3 3

//Enemy 1
#define ENEMY1_X_POS    1000
#define ENEMY1_Y_POS    350
#define ENEMY1_HEALTH   1000

//Enemy 2
#define ENEMY2_X_POS    500 - 50 * cos(game->worldTime)
#define ENEMY2_Y_POS    500 + 50 * sin(game->worldTime)
#define ENEMY2_HEALTH   2000

//Enemy 3
#define ENEMY3_X_POS    800 + 50 * cos(2*game->worldTime)
#define ENEMY3_Y_POS    700 + 50 * sin(2*game->worldTime)
#define ENEMY3_HEALTH   3000

//FPS capping
#define MAX_FPS 60
#define SCREEN_MAX_TICK_RATE 1000 / MAX_FPS

//Speed of player
#define SZYBKOSC 250

//Section about damage of player
#define HITBOX_SIZE 40
#define COOLDOWN 1 //in seconds cooldown in damage
#define PLAYER_HEALTH SCREEN_HEIGHT - SCREEN_HEIGHT / 2 //depends on window height

//Section about player bullets
#define DAMAGE_VALUE 75
#define SHOOT_SPEED 400
#define RANGE 350

//Enemy damage
#define HITBOX_ENEMY_SIZE 45
#define ENEMY_COOLDOWN 0.5 //in seconds cooldown in damage
#define ENEMY_DAMAGE_VALUE 3
#define SHOOT_COOLDOWN 0.5 //in seconds

//Modes of shooting:

//Wave
#define MAX_BULLET_AMOUNT_WAVE 100
#define SPEED_1 0.5
#define WAVE_X_MOV x - 250 * (speed * game->worldTime - i)
#define WAVE_Y_MOV y + 25 * sin(5 * (speed * game->worldTime - i))

//Spiral
#define MAX_BULLET_AMOUNT_SPIRAL 25
#define SPEED_2 1.5
#define SPIRAL_X_MOV x + 200 * game->dystans2[i] * cos (speed * game->timer - i)
#define SPIRAL_Y_MOV y + 200 * game->dystans2[i] * sin(speed * game->timer - i)

//Spiral 2
#define MAX_BULLET_AMOUNT_SPIRAL_2 20
#define SPEED_3 1
#define SPIRAL_2_X_MOV x + 200 * game->dystans3[i] * cos(3*speed * game->worldTime - i)
#define SPIRAL_2_Y_MOV y - 200 * game->dystans3[i] * sin(speed * game->worldTime - i)
#define SPIRAL_2_X_MOV_AFTER x + 200 * cos(0.5 * speed * game->worldTime - i)
#define SPIRAL_2_Y_MOV_AFTER y - 200 * sin(3 * speed * game->worldTime - i)

//Level labels
#define LEVEL_1 0
#define LEVEL_2 1
#define LEVEL_3 2

//Modes of shooting labels
#define WAVE 1
#define SPIRAL 2
#define SPIRAL_2 3

//Menu switches
#define MENU_ON 1
#define MENU_OFF 0

//Fullscreen switches
#define FULLSCREEN_ON 1
#define FULLSCREEN_OFF 0

//State switches
#define DEAD 1
#define ALIVE 0
#define WIN 2

#define MAX_STRING_LENGTH 128


void DrawString (SDL_Surface* screen, double x, double y, const char* text, SDL_Surface* charset);
void DrawSurface (SDL_Surface* screen, SDL_Surface* sprite, double x, double y);
void DrawPixel (SDL_Surface* surface, int x, int y, Uint32 color);
void DrawLine (SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle (SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
SDL_Surface* LoadBMP (char* filename, struct Game* game, struct myBullet* bullet);

bool EnemyAndBulletAnimation (struct Game* game, struct Player* player, struct myBullet* bullet, int mode, double x, double y, double speed, int level, int enemynumber);
void MyBulletAnimation (struct Game* game, struct Player* player, struct myBullet* bullet);
void AddNewBullet (struct Player* player, struct myBullet* bullet);

void InitGame (struct Game* game, struct Player* player, struct myBullet* bullet);
void ResetGame (struct Game* game, struct Player* player);
void QuitGame (struct Game* game, struct myBullet* bullet);

void WinMessage (struct Game* game, struct Player* player);
void DeathMessage (struct Game* game, struct Player* player);

void HitboxAndDamage (struct Game* game, struct Player* player, double coordX, double coordY);
void HitboxAndDamageForEnemy (struct Game* game, double coordX, double coordY);

void TimeManagement (struct Game* game, struct Player* player);
void CameraValidation (struct Game* game, struct Player* player);
void ChooseBackground (struct Game* game, struct myBullet* bullet);
void CheckKeyboard (struct Game* game, struct Player* player, struct myBullet* bullet);
void MaxScoreCalculator (struct Game* game);

void GameRender (struct Game* game, struct Player* player, struct myBullet* bullet);
void LevelRender (struct Game* game, struct Player* player, struct myBullet* bullet);

struct Game {
	SDL_Event event;
	SDL_Surface* screen = NULL, * charset = NULL, * redcharset = NULL, * plansza = NULL, * healthbar = NULL;
	SDL_Surface* me = NULL, * background1 = NULL, * background2 = NULL, * background3 = NULL, * plane = NULL, * bullet = NULL, * mybullet = NULL, * menu = NULL;
	SDL_Texture* scrtex = NULL, * plantex = NULL, * healthtex = NULL, * menutex = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int quit = 0, currentlevel = LEVEL_1, state = ALIVE, menuswitch = MENU_ON, fullscreen = FULLSCREEN_OFF;

	double dystans1[MAX_BULLET_AMOUNT_WAVE] = {};
	double dystans2[MAX_BULLET_AMOUNT_SPIRAL] = {};
	double dystans3[MAX_BULLET_AMOUNT_SPIRAL_2] = {};
	double timer = 0; //for moving in stages

	//enemy 1
	int damage1 = 0, ispresent1 = 0, health1 = ENEMY1_HEALTH;
	double enemy1X = 0, enemy1Y = 0, cooldown1 = 0;
	//enemy 2
	int damage2 = 0, ispresent2 = 0, health2 = ENEMY2_HEALTH;
	double enemy2X = 0, enemy2Y = 0, cooldown2 = 0;
	//enemy 3
	int damage3 = 0, ispresent3 = 0, health3 = ENEMY3_HEALTH;
	double enemy3X = 0, enemy3Y = 0, cooldown3 = 0;

	int enemynumberofhits = 0, maxscore = 0;

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	const SDL_Rect infobox = { 4, 4, SCREEN_WIDTH - 8, 42 };
	const SDL_Rect healthbox = { 4, SCREEN_HEIGHT / 3, 20, PLAYER_HEALTH };
	const SDL_Rect windowbox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char text[MAX_STRING_LENGTH] = {};
	int czarny = 0, zielony = 0, czerwony = 0, niebieski = 0, jasnoniebieski = 0;

	int t1 = 0, frames = 0;
	double delta = 0, worldTime = 0, fpsTimer = 0, fps = 0;

	double sumTime = 0;
};

struct Player {
	double playerX = 0, playerY = 0, x = 0, y = 0, cooldown = 0, shootcooldown = 0;
	int damage = 0, numberofhits = 0, numberofshoots = 0, score = 0;


};

struct myBullet {
	double x = 0, y = 0;
	double playerXpos = 0;
	struct myBullet* nextmyBullet = NULL;
};

#endif