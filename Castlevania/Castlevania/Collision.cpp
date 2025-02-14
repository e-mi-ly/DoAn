#include "Collision.h"
#include <algorithm>
#include <stdio.h>
using namespace std;

Collision::Collision()
{
}

bool Collision::CheckCollison(RECT r1, RECT r2)
{
	//return !(r1.left + r1.right < r2.left || r1.top + r1.bottom < r2.top || r2.left + r2.right < r1.left || r2.top + r2.bottom < r1.top);
	return !(r1.right<r2.left || r1.left>r2.right || r1.bottom<r2.top || r1.top>r2.bottom);
}

float Collision::SweptAABB(Box b1, Box b2, float & normalx, float & normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f &&  yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

bool Collision::IsStandOnGround(Box b1, Box b2)
{
	
	//Object (b1) is On the ground (b2)	
	if (b1.x + b1.w >= b2.x + b2.w)
	{
		if (b1.x - (b2.x + b2.w) > -3)
			return false;
	}
	else
	{
		if (b2.x - (b1.x + b1.w) > -3)
			return false;
	}	

	if (b1.y + b1.h >= b2.y && b1.y + b1.h - b2.y < b2.h)
		return true;	
	return false;
}

bool Collision::AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w<b2.x || b1.x>b2.x + b2.w || b1.y + b1.h<b2.y || b1.y>b2.y + b2.h);
}

int Collision::HitTheWall(Box b1, Box b2)
{
	//set va cham truc y
	if (b1.y + b1.h >= b2.y + b2.h)
	{
		if (b1.y - (b2.y + b2.h) > 0)
			return 0;
	}
	else
	{
		if (b2.y - (b1.y + b1.h) >= 0)
			return 0;
	}
	//set va cham truc x
	if (b1.x < b2.x && b1.vx > 0)
	{
		if (b1.x + b1.w + b1.vx*3 >= b2.x /*&& b1.x + b1.w - b2.x < b2.w*/)
			return 1;
	}
	if(b1.x >= b2.x && b1.vx < 0)
	{
		if (b1.x + b1.vx * 3 <=b2.x+b2.w)
			return -1;
	}	

	return 0;
}


Collision::~Collision()
{
}
