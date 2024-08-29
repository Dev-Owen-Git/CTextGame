#pragma once

#include "DataType.h"

enum class MOVE_DIR
{
	LEFT = -1,
	RIGHT = 1,
};

struct ENTITY
{
	bool IsVailed = false;

	int Hp;
	unsigned int Att;
	double Speed;

	vector2D<double> Position;
};

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

	vector2D<int> MoveDir = { 1, 1 };
};

