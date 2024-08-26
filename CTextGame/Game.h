#pragma once

#include "Utility.h"

struct Enitiy
{
	bool IsViaild = false;

	int Hp;
	int Att;

	uvector2 Position;
};

struct Bullet
{
	bool IsViaild = false;
	bool IsEmemy = false;

	int Att;

	uvector2 Position;
};

const int MAX_BULLET_COUNT = 10;
const int MAX_MONSTER_COUNT = 10;

extern Enitiy Player;
extern Enitiy Monsters[MAX_MONSTER_COUNT];
extern Bullet bullets[MAX_BULLET_COUNT];

// Monster
void LoadMonsterData();

// Player
void LoadPlayerData();

bool	PlayerInput();
int		PlayerPorcess();
int		PlayerRender();



// Bullet
int BulletProcess();
int BulletRender();

void BulletMove(Bullet& bullet);
void BulletHit(Enitiy& monster, const Bullet& bullet);


