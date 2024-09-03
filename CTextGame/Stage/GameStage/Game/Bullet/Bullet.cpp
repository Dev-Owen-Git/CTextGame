#include "Bullet.h"

#include <Stage/GameStage/Game/Entity/Entity.h>
#include <Stage/GameStage/Game/Grid/Grid.h>
#include <Stage/GameStage/Game/Player/Player.h>
#include <Stage/GameStage/Game/Monster/Monster.h>

#include <FrameRate/FrameRate.h>

#include <Utility/MathUtility.h>

#include <Renderer/Renderer.h>
#include <Data/Vector2D/Vector2D.h>

const int MAX_BULLET_COUNT = 100;
Bullet _bullets[MAX_BULLET_COUNT];


void BulletMove(vector2D<double> moveDir, Bullet* const bullet);
void BulletMoveProcess(Bullet* const bullet);
void BulletHit(ENTITY* const entity, Bullet* const bullet, const GRID_ITEM_TYPE gridType);
bool BulletCollsion(const Bullet&  bullet, ENTITY** outEntity, GRID_ITEM_TYPE* outEntityType);

bool BulletInit()
{
	ClearAllBullet();
	return true;
}

int BulletProcess()
{
	// TODO : stage monster 정보 가져오기
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = _bullets[bulletIndex];

		// 현재 활성된 총알만 체크
		if (bullet.IsViaild == false)
		{
			continue;
		}

		// 총알 충돌 처리
		ENTITY*  entity = nullptr;
		GRID_ITEM_TYPE entityType;
		if (BulletCollsion(bullet, &entity, &entityType) == true)
		{
   			BulletHit(entity,  &bullet, entityType);
		}

		// 총알 이동
		BulletMoveProcess(&bullet);
	}

    return 0;
}

int BulletRender()
{
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = _bullets[bulletIndex];

		if (bullet.IsViaild == false)
		{
			continue;
		}

		if (bullet.IsEmemy == true)
		{
			CopyDataToRendBuffer(CastingVector2D<unsigned int>(bullet.Position), 'o');
		}
		else
		{
			CopyDataToRendBuffer(CastingVector2D<unsigned int>(bullet.Position), '^');
		}

	}

    return 0;
}

void CreateBullet(const vector2D<unsigned int> spawnPoint, const int degree, const unsigned int attDamage, const BULLET_CREATOR_TYPE type)
{
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = _bullets[bulletIndex];

		if (bullet.IsViaild == false)
		{
			bullet.Position = CastingVector2D<double>(spawnPoint);
			bullet.Att = attDamage;
			bullet.moveDir = GetNormalizeDiraction<double>(degree);
			bullet.Speed = 20;
			bullet.IsEmemy = (type == BULLET_CREATOR_TYPE::MONSTER);
			bullet.IsViaild = true;
			break;
		}
	}
}

void ClearAllBullet()
{
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = _bullets[bulletIndex];
		bullet.IsViaild = false;
	}
}

void BulletMove(vector2D<double> moveDir, Bullet* const bullet)
{
	const vector2D<double> nextPosition = moveDir * (bullet->Speed * FixedDeltaTime);
	bullet->Position += nextPosition;

	if (bullet->Position.y >= MAP_HIGHT_SIZE || bullet->Position.y < 0)
	{
		bullet->IsViaild = false;
	}
}

void BulletMoveProcess(Bullet* const bullet)
{
	if (bullet->IsEmemy == true)
	{
		BulletMove({0, 1.0f}, bullet);
	}
	else
	{
		BulletMove({ 0, -1.0f }, bullet);
	}
}

void BulletHit(ENTITY* const entity, Bullet* const bullet, const GRID_ITEM_TYPE gridType)
{
	switch (gridType)
	{
	case GRID_ITEM_TYPE::PLAYER:
		PlayerHit(entity, bullet->Att);
		break;
	case GRID_ITEM_TYPE::MONSTER:
		MonsterHit(entity, bullet->Att);
		break;
	default:
		break;
	}

	// 추후 특정 총알은 관통이 가능할 시 이부분에 대해서 함수 로직 개발
	bullet->IsViaild = false;
}

bool BulletCollsion(const Bullet&  bullet, ENTITY** outEntity, GRID_ITEM_TYPE* outEntityType)
{
	if (bullet.IsEmemy == true)
	{
		(*outEntity) = (ENTITY*)GetGridItem(CastingVector2D<int>(bullet.Position), GRID_ITEM_TYPE::PLAYER);
		(*outEntityType) = GRID_ITEM_TYPE::PLAYER;
	}
	else
	{
		(*outEntity) = (ENTITY*)GetGridItem(CastingVector2D<int>(bullet.Position), GRID_ITEM_TYPE::MONSTER);
		(*outEntityType) = GRID_ITEM_TYPE::MONSTER;
	}

	return (*outEntity) != nullptr;
}