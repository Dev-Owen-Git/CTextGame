#include "Player.h"

#include "Stage.h"
#include "Renderer.h"
#include "Bullet.h"
#include "Grid.h"
#include "FrameRate.h"
#include "DataType.h"

#include <Windows.h>

PLAYER Player;

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
	vector2D<unsigned int> bulletSpawnPoint = CastingVector2D<unsigned int>(Player.Entity.Position);
	bulletSpawnPoint.y -= 1;

	CreateBullet(bulletSpawnPoint, Player.Entity.Att, BULLET_CREATOR_TYPE::PLAYER);

	Player.LastFireTime = timeGetTime();
}

void Move(MOVE_DIR dir)
{
	const vector2D<int> oldPosiiton = CastingVector2D<int>(Player.Entity.Position);

	const auto moveDirX = (int)dir * (Player.Entity.Speed * FixedTimeDelta);
	const auto nextPosition = Player.Entity.Position.x + moveDirX;
	if (nextPosition < 0 || nextPosition >= MAP_WITDH_SIZE)
	{
		return;
	}

	Player.Entity.Position.x += (int)dir * (Player.Entity.Speed * FixedTimeDelta);

	MoveGirdItem(oldPosiiton, CastingVector2D<int>(Player.Entity.Position), GRID_ITEM_TYPE::PLAYER);
}

bool PlayerInit()
{
	Player.FireCoolTime = 100;
	return false;
}

int PlayerInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		Move(MOVE_DIR::LEFT);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		Move(MOVE_DIR::RIGHT);
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
