#include <stdio.h>
#include <string.h>
#include "functions.h"

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString (SDL_Surface* screen, double x, double y, const char* text, SDL_Surface* charset) {

	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface (SDL_Surface* screen, SDL_Surface* sprite, double x, double y) {

	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

// draw a single pixel
void DrawPixel (SDL_Surface* surface, int x, int y, Uint32 color) {

	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
}

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine (SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

// draw a rectangle of size l by k
void DrawRectangle (SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

//free memory
void QuitGame (struct Game* game, struct myBullet* bullet) {

	SDL_FreeSurface(game->plane);
	SDL_FreeSurface(game->mybullet);
	SDL_FreeSurface(game->bullet);
	SDL_FreeSurface(game->background1);
	SDL_FreeSurface(game->background2);
	SDL_FreeSurface(game->background3);
	SDL_FreeSurface(game->menu);
	SDL_FreeSurface(game->me);
	SDL_FreeSurface(game->redcharset);
	SDL_FreeSurface(game->charset);
	SDL_FreeSurface(game->screen);
	SDL_FreeSurface(game->plansza);
	SDL_FreeSurface(game->healthbar);
	SDL_DestroyTexture(game->scrtex);
	SDL_DestroyTexture(game->healthtex);
	SDL_DestroyTexture(game->plantex);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();

	while (bullet->nextmyBullet != NULL) {
		void* x = bullet->nextmyBullet;
		bullet->nextmyBullet = bullet->nextmyBullet->nextmyBullet;
		free(x);
	}

}

//load BMP image
SDL_Surface* LoadBMP (char* filename, struct Game* game, struct myBullet* bullet) {

	SDL_Surface* file = SDL_LoadBMP(filename);
	if (file == NULL) {
		printf("SDL_LoadBMP(%s) error: %s\n", filename, SDL_GetError());
		QuitGame(game, bullet);
		exit(0);
	}
	return file;
}

//validate borders and camera position every frame
void CameraValidation (struct Game* game, struct Player* player) {

	//update player location
	player->playerX = START_X_POS + player->x;
	player->playerY = START_Y_POS + player->y;

	//Center the camera over the player
	game->camera.x = player->playerX - SCREEN_WIDTH / 2;
	game->camera.y = player->playerY - SCREEN_HEIGHT / 2;

	//Validate camera and player position
	if (game->camera.x < 0)
	{
		game->camera.x = 0;
	}
	if (game->camera.y < 0)
	{
		game->camera.y = 0;
	}
	if (game->camera.x > LEVEL_WIDTH - game->camera.w)
	{
		game->camera.x = LEVEL_WIDTH - game->camera.w;
	}
	if (game->camera.y > LEVEL_HEIGHT - game->camera.h)
	{
		game->camera.y = LEVEL_HEIGHT - game->camera.h;
	}
	if (player->playerX < 0)
	{
		player->playerX = 0;
		player->x = -START_X_POS;
	}
	if (player->playerY < 0)
	{
		player->playerY = 0;
		player->y = -START_Y_POS;
	}
	if (player->playerX > LEVEL_WIDTH)
	{
		player->playerX = LEVEL_WIDTH;
		player->x = LEVEL_WIDTH - START_X_POS;
	}
	if (player->playerY > LEVEL_HEIGHT)
	{
		player->playerY = LEVEL_HEIGHT;
		player->y = LEVEL_HEIGHT - START_Y_POS;
	}
}

//initiaton of the game
void InitGame (struct Game* game, struct Player* player, struct myBullet* bullet) {

	int rc;

	printf("GAME INITIALIZATION STARTED\n");
	printf("ON LEVEL %i\n",game->currentlevel+1);
	printf("PLAYER HEALTH %i\n", PLAYER_HEALTH);
	printf("TIME PASSED %f\n", game->sumTime);

	//Bullet list initialization
	AddNewBullet(player, bullet);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit(0);
	}

	//Fullscreen mode
	if (game->fullscreen) {
		rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &game->window, &game->renderer);
	}
	else {
		rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &game->window, &game->renderer);
	}
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		exit(0);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(game->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(game->window, "Planes and Missiles Game");

	//Surface initialization
	game->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

	game->healthbar = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

	game->plansza = SDL_CreateRGBSurface(0, LEVEL_WIDTH, LEVEL_HEIGHT, 32, 0, 0, 0, 0);

	//Texture initialization
	game->scrtex = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	game->plantex = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, LEVEL_WIDTH, LEVEL_HEIGHT);

	game->healthtex = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	//SDL_ShowCursor(SDL_DISABLE);

	//Load images
	game->charset = LoadBMP("./cs8x8.bmp", game, bullet);
	SDL_SetColorKey(game->charset, true, 0x000000);

	game->redcharset = LoadBMP("./cs8x8-red.bmp", game, bullet);
	SDL_SetColorKey(game->redcharset, true, 0x000000);

	game->me = LoadBMP("./me.bmp", game, bullet);

	game->background1 = LoadBMP("./sky1.bmp", game, bullet);

	game->background2 = LoadBMP("./sky2.bmp", game, bullet);

	game->background3 = LoadBMP("./sky3.bmp", game, bullet);

	game->plane = LoadBMP("./plane.bmp", game, bullet);

	game->bullet = LoadBMP("./bullet.bmp", game, bullet);

	game->mybullet = LoadBMP("./mybullet.bmp", game, bullet);

	game->menu = LoadBMP("./menu.bmp", game, bullet);

	game->menutex = SDL_CreateTextureFromSurface(game->renderer, game->menu);

	game->czarny = SDL_MapRGB(game->screen->format, 0x00, 0x00, 0x00);
	game->zielony = SDL_MapRGB(game->screen->format, 0x00, 0xFF, 0x00);
	game->czerwony = SDL_MapRGB(game->screen->format, 0xFF, 0x00, 0x00);
	game->niebieski = SDL_MapRGB(game->screen->format, 0x11, 0x11, 0xCC);
	game->jasnoniebieski = SDL_MapRGB(game->screen->format, 0x11, 0x11, 0xCC);

	MaxScoreCalculator(game);

	printf("GAME INITIALIZATION COMPLETED\n");
}

//reset game, time, damage etc.
void ResetGame (struct Game* game, struct Player* player) {

	game->state = ALIVE;
	player->x = 0;
	player->y = 0;
	for (int i = 0; i < MAX_BULLET_AMOUNT_WAVE; i++) {
		game->dystans1[i] = 0;
	}
	for (int i = 0; i < MAX_BULLET_AMOUNT_SPIRAL; i++) {
		game->dystans2[i] = 0;
	}
	for (int i = 0; i < MAX_BULLET_AMOUNT_SPIRAL_2; i++) {
		game->dystans3[i] = 0;
	}

	player->damage = 0;
	player->cooldown = 0;
	player->numberofhits = 0;
	player->numberofshoots = 0;
	game->worldTime = 0;
	game->maxscore = 0;
	game->timer = 0;
	game->enemynumberofhits = 0;
	game->ispresent1 = 0;
	game->ispresent2 = 0;
	game->ispresent3 = 0;
	game->damage1 = 0;
	game->damage2 = 0;
	game->damage3= 0;
	game->t1 = SDL_GetTicks();

}

// enemy and bullet animation mode-movement; x,y-location of enemy; 
//speed-movement and shooting speed; level-no of level where enemy is; enemynumber-no of enemy;
bool EnemyAndBulletAnimation (struct Game* game, struct Player* player, struct myBullet* bullet, int mode, double x, double y, double speed, int level, int enemynumber) {

	if (game->currentlevel == level) {

		if (enemynumber == ENEMY1) {
			sprintf(game->text, "%d/%d", game->health1 - game->damage1, game->health1);
			game->enemy1X = x;
			game->enemy1Y = y;
			game->ispresent1 = 1;
			if (game->damage1 >= game->health1) {//if enemy is dead return false
				game->ispresent1 = 0;
				return false;
			}
		}
		if (enemynumber == ENEMY2) {
			sprintf(game->text, "%d/%d", game->health2 - game->damage2, game->health2);
			game->enemy2X = x;
			game->enemy2Y = y;
			game->ispresent2 = 1;
			if (game->damage2 >= game->health2) {
				game->ispresent2 = 0;
				return false;
			}
		}
		if (enemynumber == ENEMY3) {
			sprintf(game->text, "%d/%d", game->health3 - game->damage3, game->health3);
			game->enemy3X = x;
			game->enemy3Y = y;
			game->ispresent3 = 1;
			if (game->damage3 >= game->health3) {
				game->ispresent3 = 0;
				return false;
			}
		}
		//display enemy and health
		DrawSurface(game->plansza, game->plane, x, y);
		DrawString(game->plansza, x - strlen(game->text) * 8 / 2, y-50, game->text, game->redcharset);

		if (game->timer > 30) { //timer for stages of spiral moves - reseted if 30 seconds passed
			game->timer = 0;
		}

		//mode switch
		switch (mode) {
			case WAVE: {
				for (int i = 0; i < speed * game->worldTime && i < MAX_BULLET_AMOUNT_WAVE; i++) {
					DrawSurface(game->plansza, game->bullet, WAVE_X_MOV, WAVE_Y_MOV);
					HitboxAndDamage(game, player, WAVE_X_MOV, WAVE_Y_MOV);
				}
				break;
			}
			case SPIRAL: {
				for (int i = 0; i < speed * game->timer && i < MAX_BULLET_AMOUNT_SPIRAL; i++) {
					if (game->timer < 15) {
						game->dystans2[i] += 0.2 * game->delta;
					}
					else if (game->timer > 15 && game->dystans2[i] > 0) {
						game->dystans2[i] -= 0.2 * game->delta;
					}
					DrawSurface(game->plansza, game->bullet, SPIRAL_X_MOV, SPIRAL_Y_MOV);
					HitboxAndDamage(game, player, SPIRAL_X_MOV, SPIRAL_Y_MOV);
				}
				break;
			}
			case SPIRAL_2: {
				for (int i = 0; i < speed * game->worldTime && i < MAX_BULLET_AMOUNT_SPIRAL_2; i++) {
					if (game->dystans3[i] < 1) game->dystans3[i] += 0.2 * game->delta;
					if (game->timer < 15) {
						DrawSurface(game->plansza, game->bullet, SPIRAL_2_X_MOV, SPIRAL_2_Y_MOV);
						HitboxAndDamage(game, player, SPIRAL_2_X_MOV, SPIRAL_2_Y_MOV);
					}
					else if (game->timer > 15) {
						DrawSurface(game->plansza, game->bullet, SPIRAL_2_X_MOV_AFTER, SPIRAL_2_Y_MOV_AFTER);
						HitboxAndDamage(game, player, SPIRAL_2_X_MOV_AFTER, SPIRAL_2_Y_MOV_AFTER);
					}
				}
				break;
			}
			default: {
				printf("CHOOSE CORRECT MODE");
				QuitGame(game, bullet);
				exit(0);
			}
		}
		return true;
	}
	return false;
}

//animations for bullets sent by player
void MyBulletAnimation (struct Game* game, struct Player* player, struct myBullet* bullet) {

	bullet = bullet->nextmyBullet;
	while (bullet->nextmyBullet != NULL && bullet->x < bullet->playerXpos + RANGE) {
		bullet->x += SHOOT_SPEED * game->delta;
		DrawSurface(game->plansza, game->mybullet, bullet->x, bullet->y);
		HitboxAndDamageForEnemy(game, bullet->x, bullet->y);
		bullet = bullet->nextmyBullet;
	}
}

//calculate damage of player
void HitboxAndDamage (struct Game* game, struct Player* player, double coordX, double coordY) {

	if ((player->playerX - coordX) * (player->playerX - coordX) + (player->playerY - coordY) * (player->playerY - coordY) < HITBOX_SIZE * HITBOX_SIZE && player->cooldown > COOLDOWN) {
		player->damage += SCREEN_HEIGHT / 100 * ENEMY_DAMAGE_VALUE;
		printf("DAMAGE %i/%i\n", player->damage, PLAYER_HEALTH);
		player->cooldown = 0;
		player->numberofhits++;
	}
}

//add new bullet to list
void AddNewBullet (struct Player* player, struct myBullet* bullet) {

	myBullet *x = (myBullet*)malloc(sizeof(myBullet));

	x->x = player->playerX;
	x->playerXpos = player->playerX;
	x->y = player->playerY;
	x->nextmyBullet = bullet->nextmyBullet;
	bullet->nextmyBullet = x;

}

//calculate damage of enemies
void HitboxAndDamageForEnemy (struct Game* game, double coordX, double coordY) {

	if (game->ispresent1) {
		if ((game->enemy1X - coordX) * (game->enemy1X - coordX) + (game->enemy1Y - coordY) * (game->enemy1Y - coordY) < HITBOX_ENEMY_SIZE * HITBOX_ENEMY_SIZE && game->cooldown1 > ENEMY_COOLDOWN) {
			game->damage1 += DAMAGE_VALUE;
			printf("DAMAGE FOR ENEMY 1 %i/%i\n", game->damage1, ENEMY1_HEALTH);
			game->cooldown1 = 0;
			game->enemynumberofhits++;
		}
	}
	if (game->ispresent2) {
		if ((game->enemy2X - coordX) * (game->enemy2X - coordX) + (game->enemy2Y - coordY) * (game->enemy2Y - coordY) < HITBOX_ENEMY_SIZE * HITBOX_ENEMY_SIZE && game->cooldown2 > ENEMY_COOLDOWN) {
			game->damage2 += DAMAGE_VALUE;
			printf("DAMAGE FOR ENEMY 2 %i/%i\n", game->damage2, ENEMY2_HEALTH);
			game->cooldown2 = 0;
			game->enemynumberofhits++;
		}
	}
	if (game->ispresent3) {
		if ((game->enemy3X - coordX) * (game->enemy3X - coordX) + (game->enemy3Y - coordY) * (game->enemy3Y - coordY) < HITBOX_ENEMY_SIZE * HITBOX_ENEMY_SIZE && game->cooldown3 > ENEMY_COOLDOWN) {
			game->damage3 += DAMAGE_VALUE;
			printf("DAMAGE FOR ENEMY 3 %i/%i\n", game->damage3, ENEMY3_HEALTH);
			game->cooldown3 = 0;
			game->enemynumberofhits++;
		}
	}
}

//choose background depending on level
void ChooseBackground (struct Game* game, struct myBullet* bullet) {

	switch (game->currentlevel) {
	case LEVEL_1: {
		DrawSurface(game->plansza, game->background1, LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2);
		break;
	}
	case LEVEL_2: {
		DrawSurface(game->plansza, game->background2, LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2);
		break;
	}
	case LEVEL_3: {
		DrawSurface(game->plansza, game->background3, LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2);
		break;
	}
	default: {
		printf("CHOOSE CORRECT LEVEL");
		QuitGame(game, bullet);
		exit(0);
	}
	}
}

//check keyboard state
void CheckKeyboard (struct Game* game, struct Player* player, struct myBullet* bullet) {

	const Uint8* keypressed = SDL_GetKeyboardState(NULL);

	if (game->menuswitch == MENU_OFF) {
		if (game->state == ALIVE) {
			if (keypressed[SDL_SCANCODE_UP]) {
				player->y -= SZYBKOSC * game->delta;
			}
			if (keypressed[SDL_SCANCODE_DOWN]) {
				player->y += SZYBKOSC * game->delta;
			}
			if (keypressed[SDL_SCANCODE_LEFT]) {
				player->x -= SZYBKOSC * game->delta;
			}
			if (keypressed[SDL_SCANCODE_RIGHT]) {
				player->x += SZYBKOSC * game->delta;
			}
			if (keypressed[SDL_SCANCODE_SPACE] && player->shootcooldown > SHOOT_COOLDOWN) {
				AddNewBullet(player, bullet);
				player->shootcooldown = 0;
				player->numberofshoots++;
			}
		}
		if (keypressed[SDL_SCANCODE_N]) {
			if (game->state == WIN && game->currentlevel != LEVEL_3) game->currentlevel++;
			else if (game->state == WIN && game->currentlevel == LEVEL_3) game->currentlevel = LEVEL_1;
			QuitGame(game, bullet);
			ResetGame(game, player);
			InitGame(game, player, bullet);
			game->menuswitch = MENU_OFF;
		}
		if (keypressed[SDL_SCANCODE_M]) {
			QuitGame(game, bullet);
			ResetGame(game, player);
			InitGame(game, player, bullet);
			game->menuswitch = MENU_ON;
			game->sumTime = 0;
		}
	}
	else if (game->menuswitch == MENU_ON) {
		if (keypressed[SDL_SCANCODE_1]) {
			game->menuswitch = MENU_OFF;
			game->currentlevel = LEVEL_1;
			QuitGame(game, bullet);
			ResetGame(game, player);
			InitGame(game, player, bullet);
		}
		if (keypressed[SDL_SCANCODE_2]) {
			game->menuswitch = MENU_OFF;
			game->currentlevel = LEVEL_2;
			QuitGame(game, bullet);
			ResetGame(game, player);
			InitGame(game, player, bullet);
		}
		if (keypressed[SDL_SCANCODE_3]) {
			game->menuswitch = MENU_OFF;
			game->currentlevel = LEVEL_3;
			QuitGame(game, bullet);
			ResetGame(game, player);
			InitGame(game, player, bullet);
		}
		if (keypressed[SDL_SCANCODE_F11]) {
			if (game->fullscreen) {
				game->fullscreen = FULLSCREEN_OFF;
			}
			else {
				game->fullscreen = FULLSCREEN_ON;
			}
			QuitGame(game, bullet);
			ResetGame(game, player);
			InitGame(game, player, bullet);
			game->menuswitch = MENU_ON;
		}
	}
	if (keypressed[SDL_SCANCODE_ESCAPE]) {
		game->quit = 1;
	}
	while (SDL_PollEvent(&game->event)) {
		if (game->event.type == SDL_QUIT) {
			game->quit = 1;
		}
	}
}

//displaying death message
void DeathMessage (struct Game* game, struct Player* player) {

	game->state = DEAD;
	player->x = 0;
	player->y = 0;
	game->sumTime += game->worldTime;
	SDL_FillRect(game->plansza, NULL, game->czarny);
	sprintf(game->text, "NIE ZYJESZ, N - SPROBUJ PONOWNIE, M - MENU");
	DrawString(game->plansza, game->plansza->w / 2 - strlen(game->text) * 8 / 2, game->plansza->h / 2, game->text, game->charset);
	sprintf(game->text, "TWOJ CZAS %.1f S; W SUMIE %.1f S; OCENA %d/%d", game->worldTime, game->sumTime, player->score, game->maxscore);
	DrawString(game->plansza, game->plansza->w / 2 - strlen(game->text) * 8 / 2, game->plansza->h / 2 + 16, game->text, game->charset);
}

//displaying win message
void WinMessage (struct Game* game, struct Player* player) {

	game->state = WIN;
	player->x = 0;
	player->y = 0;
	game->sumTime += game->worldTime;
	SDL_FillRect(game->plansza, NULL, game->czarny);
	sprintf(game->text, "WYGRALES, N - KOLEJNY POZIOM, M - MENU");
	if (game->currentlevel == LEVEL_3) {
		sprintf(game->text, "WYGRALES, N - SPROBUJ OD NOWA, M - MENU");
	}
	DrawString(game->plansza, game->plansza->w / 2 - strlen(game->text) * 8 / 2, game->plansza->h / 2, game->text, game->charset);
	sprintf(game->text, "TWOJ CZAS %.1f S; W SUMIE %.1f S; OCENA %d/%d", game->worldTime, game->sumTime, player->score, game->maxscore);
	DrawString(game->plansza, game->plansza->w / 2 - strlen(game->text) * 8 / 2, game->plansza->h / 2 + 16, game->text, game->charset);
}

void TimeManagement (struct Game* game, struct Player* player) {

	static int t2;

	t2 = SDL_GetTicks();

	// here t2-t1 is the time in milliseconds since
	// the last screen was drawn
	// delta is the same time in seconds

	game->delta = (t2 - game->t1) * 0.001;

	game->t1 = t2;

	if (game->state == ALIVE) { //if player is alive
		game->worldTime += game->delta;
		game->timer += game->delta;
		if (player->cooldown < COOLDOWN) {
			player->cooldown += game->delta;
		}
		if (player->shootcooldown < SHOOT_COOLDOWN) {
			player->shootcooldown += game->delta;
		}
		if (game->cooldown1 < ENEMY_COOLDOWN) {
			game->cooldown1 += game->delta;
		}
		if (game->cooldown2 < ENEMY_COOLDOWN) {
			game->cooldown2 += game->delta;
		}
		if (game->cooldown3 < ENEMY_COOLDOWN) {
			game->cooldown3 += game->delta;
		}
	}

	game->fpsTimer += game->delta;

	//calculate fps
	if (game->fpsTimer > 0.5) {
		game->fps = game->frames * 2;
		game->frames = 0;
		game->fpsTimer -= 0.5;
	}
}

void LevelRender (struct Game* game, struct Player* player, struct myBullet* bullet) {

	SDL_FillRect(game->screen, NULL, game->czarny);

	SDL_FillRect(game->healthbar, NULL, game->czarny);

	SDL_FillRect(game->plansza, NULL, game->czarny);

	ChooseBackground(game, bullet);

	//render player sprite
	DrawSurface(game->plansza, game->me, player->playerX, player->playerY);

	//display cooldown information
	if (player->cooldown < COOLDOWN) {
		sprintf(game->text, "%.1lf s", player->cooldown);
		DrawString(game->plansza, player->playerX - strlen(game->text) * 8 / 2, player->playerY - 50, game->text, game->redcharset);
	}
	//level 1

	EnemyAndBulletAnimation(game, player, bullet, WAVE,
		ENEMY1_X_POS, ENEMY1_Y_POS, SPEED_1, LEVEL_1, ENEMY1);

	//level 2

	EnemyAndBulletAnimation(game, player, bullet, SPIRAL,
		ENEMY2_X_POS, ENEMY2_Y_POS, SPEED_2, LEVEL_2, ENEMY2);

	//level 3

	EnemyAndBulletAnimation(game, player, bullet, SPIRAL_2,
		ENEMY3_X_POS, ENEMY3_Y_POS, SPEED_3, LEVEL_3, ENEMY3);

	MyBulletAnimation(game, player, bullet);
}

void MaxScoreCalculator (struct Game* game) {
	
	double sumofenemyhealth = 0;

	if (game->currentlevel == LEVEL_1)
	{
		sumofenemyhealth += ENEMY1_HEALTH;
	}
	if (game->currentlevel == LEVEL_2)
	{
		sumofenemyhealth += ENEMY2_HEALTH;
	}
	if (game->currentlevel == LEVEL_3)
	{
		sumofenemyhealth += ENEMY3_HEALTH;
	}

	game->maxscore = 4 * ceil (sumofenemyhealth / DAMAGE_VALUE);

}

//rendering and displaying whole game
void GameRender(struct Game* game, struct Player* player, struct myBullet* bullet) {

	while (!game->quit) { //main loop

		//validate camera position
		CameraValidation(game, player);

		//Manage time spent
		TimeManagement(game, player);

		//render this part only if menu is off
		if (game->menuswitch == MENU_OFF && game->state == ALIVE) {

			player->score = START_SCORE_VALUE + 5 * game->enemynumberofhits - 3 * player->numberofhits - player->numberofshoots;

			//if player health is at minimum
			if (player->damage >= PLAYER_HEALTH)
			{
				DeathMessage(game, player);
			}

			//if every enemy is dead
			else if ((game->ispresent1 && !(game->ispresent2) && !(game->ispresent3) && (game->damage1 >= game->health1))
				|| (game->ispresent2 && !(game->ispresent1) && !(game->ispresent3) && (game->damage2 >= game->health2))
				|| (game->ispresent3 && !(game->ispresent1) && !(game->ispresent2) && (game->damage3 >= game->health3)))
			{
				WinMessage(game, player);
			}
			//else render level
			else {
				LevelRender(game, player, bullet);
				sprintf(game->text, "Poziom %i, czas trwania = %.1lf s %.0lf klatek / s ocena = %d/%d", game->currentlevel + 1, game->worldTime, game->fps, player->score, game->maxscore);
			}
			// info text
			DrawRectangle(game->screen, 4, 4, SCREEN_WIDTH - 8, 42, game->czerwony, game->niebieski);
			DrawRectangle(game->healthbar, 4, SCREEN_HEIGHT / 3 + player->damage, 20, PLAYER_HEALTH - player->damage, game->czarny, game->czerwony);
			DrawString(game->screen, game->screen->w / 2 - strlen(game->text) * 8 / 2, 10, game->text, game->charset);
			sprintf(game->text, "Esc - wyjscie, n - nowa gra, m - menu");
			DrawString(game->screen, game->screen->w / 2 - strlen(game->text) * 8 / 2, 22, game->text, game->charset);
			sprintf(game->text, "\030\032\031\033 - sterowanie, spacja - strzal");
			DrawString(game->screen, game->screen->w / 2 - strlen(game->text) * 8 / 2, 34, game->text, game->charset);
		}
		//render section
		SDL_RenderClear(game->renderer);

		//menu render
		if (game->menuswitch == MENU_ON) {
			SDL_RenderCopy(game->renderer, game->menutex, NULL, NULL);
		}

		else if (game->menuswitch == MENU_OFF) {
			SDL_UpdateTexture(game->scrtex, NULL, game->screen->pixels, game->screen->pitch);
			SDL_UpdateTexture(game->healthtex, NULL, game->healthbar->pixels, game->healthbar->pitch);
			SDL_UpdateTexture(game->plantex, NULL, game->plansza->pixels, game->plansza->pitch);
			SDL_RenderCopy(game->renderer, game->plantex, &game->camera, &game->windowbox);
			SDL_RenderCopy(game->renderer, game->scrtex, &game->infobox, &game->infobox);
			SDL_RenderCopy(game->renderer, game->healthtex, &game->healthbox, &game->healthbox);
		}

		SDL_RenderPresent(game->renderer);

		//fps capping section
		if (game->fpsTimer < SCREEN_MAX_TICK_RATE)
		{
			SDL_Delay(SCREEN_MAX_TICK_RATE - game->fpsTimer);
		}

		// handling of events

		CheckKeyboard(game, player, bullet);

		game->frames++;
	}
}