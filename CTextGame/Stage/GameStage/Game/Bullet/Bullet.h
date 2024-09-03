#pragma once

#include <Data/DataType.h>

struct Bullet
{
	bool IsViaild = false;
	bool IsEmemy = false;

	unsigned int Att;
	double Speed;

	vector2D<double> moveDir;
	vector2D<double> Position;
};

enum class BULLET_CREATOR_TYPE
{
	PLAYER,
	MONSTER,
};

bool BulletInit();
int BulletProcess();
int BulletRender();

void CreateBullet(const vector2D<unsigned int> spawnPoint, const int degree, const unsigned int attDamage, const BULLET_CREATOR_TYPE type);
void ClearAllBullet();