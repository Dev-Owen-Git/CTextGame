#include "Player.h"

#include "Stage.h"
#include "Renderer.h"
#include "Bullet.h"
#include "Grid.h"
#include "FrameRate.h"
#include "DataType.h"

#include <Windows.h>

PLAYER Player;

// Attack
bool PlayerFireCoolDown();
void FirePlayerBullet();

// Move
void Move(const vector2D<double> dir);

bool PlayerInit()
{
	Player.FireCoolTime = 100;
	return false;
}

int PlayerInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		Move({1, 0});
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		Move({ 0, -1 });
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (PlayerFireCoolDown() == true)
		{
			FirePlayerBullet();
		}
	}

	return 0;
}

int PlayerPorcess()
{
	return 0;
}

int PlayerRender()
{
	if (Player.Entity.IsVailed == true)
	{
		CopyDataToRendBuffer(CastingVector2D<unsigned int>(Player.Entity.Position), "P");
	}
	return 0;
}

void PlayerHit(ENTITY* const entity, const int damage)
{
	entity->Hp -= damage;

	if (entity->Hp <= 0)
	{
		entity->IsVailed = false;
		RemoveGridItem(CastingVector2D<int>(entity->Position), GRID_ITEM_TYPE::PLAYER);

		SetStage(StageType::Over);
	}
}

void LoadPlayerData(const STAGE_FILE_INFO* stageData)
{
	Player.Entity.Hp = 10;
	Player.Entity.Att = 10;
	Player.Entity.Speed = 10;

	Player.FireCoolTime = 100;

	Player.Entity.Position = stageData->PlayerSpawnPoint;

	SetGridItem(CastingVector2D<int>(Player.Entity.Position), &Player, GRID_ITEM_TYPE::PLAYER);

	Player.Entity.IsVailed = true;
}











// PLAYER ATTACK
bool PlayerFireCoolDown()
{
	if (Player.LastFireTime + Player.FireCoolTime <= timeGetTime())
	{
		return true;
	}
	return false;
}

void FirePlayerBullet()
{
	static const int FireDregree = 90;
	static const vector2D<int> FireSpawnOffset = vector2D<int>{ 0, -1 };

	// create bullet
	const vector2D<unsigned int> bulletSpawnPoint = CastingVector2D<unsigned int>(Player.Entity.Position) + FireSpawnOffset;
	CreateBullet(bulletSpawnPoint, FireDregree, Player.Entity.Att, BULLET_CREATOR_TYPE::PLAYER);

	// reset fire
	Player.LastFireTime = timeGetTime();
}






// Player Move
void Move(const vector2D<double> dir)
{
	const vector2D<int>		oldPoint		= CastingVector2D<int>(Player.Entity.Position);
	const vector2D<double>	moveDir			= dir * (Player.Entity.Speed * FixedDeltaTime);
	const vector2D<double>	nextMovePoint	= Player.Entity.Position + moveDir;

	if (nextMovePoint.x < 0 || nextMovePoint.x >= MAP_WITDH_SIZE)
	{
		return;
	}

	Player.Entity.Position = nextMovePoint;
	MoveGirdItem(oldPoint, CastingVector2D<int>(Player.Entity.Position), GRID_ITEM_TYPE::PLAYER);
}
