#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "functions.h"

#ifdef __cplusplus
extern "C"
#endif


int main(int argc, char** argv) {

	struct Game default1;
	struct Game* game = &default1;

	struct Player default2;
	struct Player* player = &default2;

	struct myBullet default3;
	struct myBullet* bullet = &default3;

	InitGame(game, player, bullet);

	game->t1 = SDL_GetTicks();

	GameRender(game, player, bullet);

	QuitGame(game, bullet);
	return 0;
};
