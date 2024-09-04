#pragma once

#include <Data/Vector2D/Vector2D.h>

struct ENTITY
{
	bool IsVailed = false;

	int Hp;
	unsigned int Att;
	double Speed;

	vector2D<double> Position;
};

void InitEntity(ENTITY* const entity, const unsigned int hp, const unsigned att, const double speed, const vector2D<double> position);

struct PLAYER
{
	ENTITY Entity;

	unsigned int LastFireTime;
	unsigned int FireCoolTime;
};

struct MONSTER
{
	ENTITY Entity;

	unsigned char Sprite;

	unsigned int LastFireTime;
	unsigned int FireCoolTime;
	unsigned int FireCoolTimeRange;

	unsigned int MoveType;

	vector2D<double> MoveDir = { 0, 0 };
};

