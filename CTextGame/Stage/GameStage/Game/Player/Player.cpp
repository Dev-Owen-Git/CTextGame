#include "Player.h"

#include <Stage/Stage.h>
#include <Stage/GameStage/Game/Grid/Grid.h>
#include <Stage/GameStage/Game/Bullet/Bullet.h>

#include <Renderer/Renderer.h>

#include <FrameRate/FrameRate.h>

#include <Data/Vector2D/Vector2D.h>

#include <Windows.h>

PLAYER Player;

// Attack
bool PlayerFireCoolDown();
void FirePlayerBullet();

// Move
void Move(const vector2D<double> dir);

bool PlayerInit()
{
	return true;
}

int PlayerInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		static const vector2D<double> LeftMoveDir = { -1, 0 };
		Move(LeftMoveDir);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		static const vector2D<double> RightMoveDir = { 1, 0 };
		Move(RightMoveDir);
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

void OnPlayerDead(ENTITY* const entity)
{
	// 비활성화
	EntityUnVailed(entity, true, GRID_ITEM_TYPE::PLAYER);

	// 게임 종료
	SetStage(StageType::Over);
}

void LoadPlayerData(const STAGE_FILE_INFO& stageData)
{
	const unsigned int	DEFAULT_HP = 10;
	const unsigned int	DEFAULT_ATTACK = 10;
	const double		DEFAULT_SPEED = 10;

	// Init Entiy
	InitEntity(&Player.Entity, DEFAULT_HP, DEFAULT_ATTACK, DEFAULT_SPEED, stageData.PlayerSpawnPoint);
		
	// Attack Cool
	Player.FireCoolTime = 100;

	SetGridItem(CastingVector2D<int>(Player.Entity.Position), &Player, GRID_ITEM_TYPE::PLAYER);
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
	static const int FireDregree = 270;
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
	const vector2D<int>		currentPoint		= CastingVector2D<int>(Player.Entity.Position);
	const vector2D<double>	moveDir			= dir * (Player.Entity.Speed * FixedDeltaTime);
	const vector2D<double>	nextMovePoint	= Player.Entity.Position + moveDir;

	if (nextMovePoint.x < 0 || nextMovePoint.x >= MAP_WITDH_SIZE)
	{
		return;
	}

	Player.Entity.Position = nextMovePoint;
	MoveGirdItem(currentPoint, CastingVector2D<int>(Player.Entity.Position), GRID_ITEM_TYPE::PLAYER);
}
