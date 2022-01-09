#pragma once
#include <iostream>
#include <SDL.h>

class Snake
{
private:

	class SnakePart
	{
	public:	
		int direction = -1;
		int speed = 3;
		SnakePart* next, *prev;
		SnakePart(int direction, int speed, SnakePart* pr = NULL);
		SnakePart(const SnakePart& s);
		~SnakePart();

		void AddPart(int direction, int speed);
	};

	SDL_Rect rects[384];
	SDL_Rect dst_pl = { 600, 400, 50, 50};
	SnakePart* head;
	bool isDead = false;
	bool portals = true;

public:

	Snake();
	Snake(const Snake& s);
	~Snake();

	int GetDirection();
	void SetDirection(int dir);
	
	int* GetPartsDirections();
	void SetPartsDirections();
	
	int GetSpeed();
	bool IsPortals();

	void Grow();
	void Death();

	SDL_Rect GetHeaddst();
	void SetHeaddst(int x = 0, int y = 0, int w = 50, int h = 50);
	SDL_Rect* SetSnakedst();
	SDL_Rect* GetSnakedst();
};