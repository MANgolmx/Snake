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

	SDL_Rect snakeParts[384];
	SDL_Rect dst_pl = { 550, 350, 50, 50};
	SnakePart* head;
	int score;
	int bestScore;
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
	void SetPortals(bool port);

	void SaveScore();
	int GetScore();
	void ReadScore();

	void Grow(int direction = -1);
	void Death();

	void Clear();
	void Revive();

	SDL_Rect GetHeaddst();
	void SetHeaddst(int x = 0, int y = 0, int w = 50, int h = 50);
	SDL_Rect* SetSnakedst();
	SDL_Rect* GetSnakedst();
};