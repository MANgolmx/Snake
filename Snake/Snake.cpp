#include "Snake.h"
#include <iostream>

Snake::Snake()
{
	head = new SnakePart(0, 50);
	this->Grow();
	this->Grow();
	this->Grow();
}

Snake::Snake(const Snake& s)
{
	head = s.head;
}

Snake::~Snake()
{
	head = NULL;
}

int Snake::GetDirection()
{
	return head->direction;
}

void Snake::SetDirection(int dir)
{
	head->direction = dir;
}

void Snake::SetPartsDirections()
{
	SnakePart* tmp = head;
	int i = 0;
	for (tmp; tmp->next != NULL; tmp = tmp->next);
	for (tmp; tmp->prev != NULL; tmp = tmp->prev) {
		tmp->direction = tmp->prev->direction;
	}
}

int Snake::GetSpeed()
{
	return head->speed;
}

bool Snake::IsPortals()
{
	return portals;
}

void Snake::Grow()
{
	SnakePart* tmp;
	for (tmp = head; tmp->next != NULL; tmp = tmp->next);
	tmp->AddPart(tmp->direction, GetSpeed());
}

void Snake::Death()
{
	isDead = true;
}

SDL_Rect Snake::GetHeaddst()
{
	return dst_pl;
}

void Snake::SetHeaddst(int x, int y, int w, int h)
{
	dst_pl.x = x;
	if (portals && x >= 1200) dst_pl.x = 0;
	else if (portals && x < 0) dst_pl.x = 1150;
	dst_pl.y = y;
	if (portals && y >= 800) dst_pl.y = 0;
	if (portals && y < 0) dst_pl.y = 750;
	dst_pl.w = w;
	dst_pl.h = h;
}

SDL_Rect* Snake::SetSnakedst()
{
	SnakePart* tmp;
	int counter = 0;
	for (tmp = head; tmp != NULL; tmp = tmp->next)
	{
		rects[counter].w = rects[counter].h = 50;
		int x = this->GetHeaddst().x;
		int y = this->GetHeaddst().y;
		int counter2 = 0;
		if (!isDead && !portals)
			for (SnakePart* tmp2 = head; tmp2 != tmp; tmp2 = tmp2->next)
			{
				     if (this->GetPartsDirections()[counter2] == 0) y += 50;
				else if (this->GetPartsDirections()[counter2] == 1) x -= 50;
				else if (this->GetPartsDirections()[counter2] == 2) y -= 50;
				else if (this->GetPartsDirections()[counter2] == 3) x += 50;
				counter2++;
			}
		if(!isDead && portals)
			for (SnakePart* tmp2 = head; tmp2 != tmp; tmp2 = tmp2->next)
			{
				     if (this->GetPartsDirections()[counter2] == 0) y += 50;
				else if (this->GetPartsDirections()[counter2] == 1) x -= 50;
				else if (this->GetPartsDirections()[counter2] == 2) y -= 50;
				else if (this->GetPartsDirections()[counter2] == 3) x += 50;
				if (y >= 800) y = 0;
				if (x < 0) x = 1150;
				if (x >= 1200) x = 0;
				if (y < 0) y = 750;
				counter2++;
			}
		rects[counter].x = x;
		rects[counter].y = y;
		counter++;
	}
	return rects;
}

SDL_Rect* Snake::GetSnakedst()
{
	return rects;
}

Snake::SnakePart::SnakePart(int dir, int sp, SnakePart* pr)
{
	this->direction = dir;
	this->speed = sp;
	next = NULL;
	if (pr != NULL) {
		prev = pr;
		pr->next = this;
	}
	else prev = NULL;
}

Snake::SnakePart::SnakePart(const SnakePart& s)
{
	direction = s.direction;
	speed = s.speed;
	next = s.next;
	prev = s.prev;
}

Snake::SnakePart::~SnakePart()
{
}

void Snake::SnakePart::AddPart(int direction, int speed)
{
	this->next = new SnakePart(direction, speed, this);
}

int* Snake::GetPartsDirections()
{
	int mas[384];
	SnakePart* tmp = head;
	for (int i = 0; i < 384; i++)
	{
		if (tmp->next == NULL) mas[i] = -1;
		else
		{
			mas[i] = tmp->direction;
			tmp = tmp->next;
		}
	}
	return mas;
}
