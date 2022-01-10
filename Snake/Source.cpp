#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Snake.h"

#define BL_SIZE 50

int random(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

bool isBelong(int x, int y, SDL_Rect r)
{
	if (x >= r.x && x <= r.x + r.w &&
		y >= r.y && y <= r.y + r.h)
		return true;
	return false;
}

int main(int argc, char** argv)
{
	srand(time(0));
	Snake snake;

#pragma region initialization

	int win_width = 1200, win_height = 800;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Couldn't init SDL!  %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Window* win = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height,
		(SDL_WINDOW_SHOWN));
	if (win == NULL)
	{
		printf("Couldn't create window!  %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Couldn't create window!  %s\n", SDL_GetError());
		exit(1);
	}

	int r = IMG_Init(IMG_INIT_PNG);
	if (!(r & IMG_INIT_PNG))
		printf("We cann't use PNG files!");

	if (TTF_Init() != 0) {
		printf("TTF Init error %s\n", TTF_GetError());
		exit(2);
	}

	bool isRunning = true;
	bool inMenu = true;
	bool inSettings = false;
	int counter, counter2;
	int delay = 400;
	int sq;

	SDL_Event ev;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	SDL_Rect src;
	
	SDL_Surface* surf = IMG_Load("Images/SnakePart.png");
	if (surf == NULL)
	{
		printf("Picture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Texture* tex_pl = SDL_CreateTextureFromSurface(ren, surf);
	if (tex_pl == NULL)
	{
		printf("Texture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	surf = IMG_Load("Images/Apple.png");
	if (surf == NULL)
	{
		printf("Picture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Rect dst_ap = { 150, 600, surf->w, surf->h};
	SDL_Texture* tex_ap = SDL_CreateTextureFromSurface(ren, surf);
	if (tex_ap == NULL)
	{
		printf("Texture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	surf = IMG_Load("Images/START.png");
	if (surf == NULL)
	{
		printf("Picture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Rect dst_st = { win_width / 2 - surf->w / 2, win_height / 2 - 80, surf->w, surf->h };
	SDL_Texture* tex_st = SDL_CreateTextureFromSurface(ren, surf);
	if (tex_st == NULL)
	{
		printf("Texture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	

	/*
	SDL_Texture* tex_bg = SDL_CreateTextureFromSurface(ren, surf);
	if (tex_bg == NULL)
	{
		printf("Texture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}


	surf = IMG_Load("Images/Flag.png");
	if (surf == NULL)
	{
		printf("Picture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Rect dst_fl = { 100, 100, surf->w * scale_fl, surf->h * scale_fl };

	SDL_Texture* tex_fl = SDL_CreateTextureFromSurface(ren, surf);
	if (tex_pl == NULL)
	{
		printf("Texture wasn't load!  %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(surf);
	*/

#pragma endregion initialization

	while (isRunning)
	{
		
#pragma region event handling

		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT: isRunning = false; break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE: isRunning = false; break;
				case SDL_SCANCODE_UP: if (snake.GetDirection() != 2) snake.SetDirection(0); break;
				case SDL_SCANCODE_RIGHT: if (snake.GetDirection() != 3) snake.SetDirection(1); break;
				case SDL_SCANCODE_DOWN: if (snake.GetDirection() != 0) snake.SetDirection(2); break;
				case SDL_SCANCODE_LEFT: if (snake.GetDirection() != 1) snake.SetDirection(3); break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				int mx, my;
				SDL_GetMouseState(&mx, &my);
				if (isBelong(mx, my, dst_st)) {
					inMenu = false;
					SDL_DestroyTexture(tex_st);
				}
				break;
			}
		}

#pragma endregion event handling


#pragma region logic

		if (!inMenu && !inSettings)
		{
			counter2 = 0;
			if (snake.GetHeaddst().x == dst_ap.x &&
				snake.GetHeaddst().y == dst_ap.y)
			{
				snake.Grow();
				delay--;

			randomize:
				sq = random(0, 345);
				while (snake.GetSnakedst()[counter2].w == BL_SIZE) {
					if (snake.GetSnakedst()[counter2].x == sq % 23 * BL_SIZE &&
						snake.GetSnakedst()[counter2].y == sq % 15 * BL_SIZE)
						goto randomize;
					counter2++;
				}
				dst_ap = { sq % 23 * BL_SIZE, sq % 15 * BL_SIZE, BL_SIZE, BL_SIZE };
			}

			switch (snake.GetDirection())
			{
			case 0: snake.SetHeaddst(snake.GetHeaddst().x, snake.GetHeaddst().y - snake.GetSpeed(), snake.GetHeaddst().w, snake.GetHeaddst().h); break;
			case 1:	snake.SetHeaddst(snake.GetHeaddst().x + snake.GetSpeed(), snake.GetHeaddst().y, snake.GetHeaddst().w, snake.GetHeaddst().h); break;
			case 2: snake.SetHeaddst(snake.GetHeaddst().x, snake.GetHeaddst().y + snake.GetSpeed(), snake.GetHeaddst().w, snake.GetHeaddst().h); break;
			case 3:	snake.SetHeaddst(snake.GetHeaddst().x - snake.GetSpeed(), snake.GetHeaddst().y, snake.GetHeaddst().w, snake.GetHeaddst().h); break;
			}

			if (!snake.IsPortals() &&
					(snake.GetHeaddst().x < 0 ||
					snake.GetHeaddst().x + snake.GetHeaddst().w > win_width ||
					snake.GetHeaddst().y < 0 ||
					snake.GetHeaddst().y + snake.GetHeaddst().h > win_height))
				snake.Death();

			snake.SetSnakedst();

			counter = 1;
			while (snake.GetSnakedst()[counter].w == BL_SIZE)
			{
				if (snake.GetSnakedst()[counter].x == snake.GetHeaddst().x &&
					snake.GetSnakedst()[counter].y == snake.GetHeaddst().y)
					snake.Death();
				counter++;
			}

		}

#pragma endregion logic


#pragma region rendering

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		if (inMenu) {
			SDL_RenderCopyEx(ren, tex_st, NULL, &dst_st, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(ren);
		}
		if (!inMenu && !inSettings) {
			counter = 0;
			while (snake.GetSnakedst()[counter].w == BL_SIZE) {
				SDL_RenderCopyEx(ren, tex_pl, NULL, &snake.GetSnakedst()[counter], 0, NULL, SDL_FLIP_NONE);
				counter++;
			}
			SDL_RenderCopyEx(ren, tex_ap, NULL, &dst_ap, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(ren);

			SDL_Delay(delay);

			snake.SetPartsDirections();
			snake.SetSnakedst();
		}

#pragma endregion rendering

	}

#pragma region end

	SDL_DestroyTexture(tex_pl);
	SDL_DestroyTexture(tex_ap);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;

#pragma endregion end


}