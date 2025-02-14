#pragma once
#include "Enemy.h"
#include "EnemyRender.h"

class Bat : public Enemy
{
private:
	float temp;
	int direction;
	bool IsFight;
public:
	Bat();
	Bat(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	Box GetBoundBox();
	~Bat();
};

