#include "Bullet.h"

#include "Entity.h"
#include "Grid.h"
#include "Player.h"
#include "Monster.h"
#include "FrameRate.h"

#include "Renderer.h"

const int MAX_BULLET_COUNT = 100;
Bullet _bullets[MAX_BULLET_COUNT];

// 총알이 이동 후 맵 밖으로 나가면 제거

void PlayerBulletMove(Bullet* const bullet)
{
	static int moveYDir = -1;
	bullet->Position.y += moveYDir * (bullet->Speed * FixedTimeDelta);

	if (bullet->Position.y < 0.0f)
	{
		bullet->IsViaild = false;
	}
}

void MonsterBulletMove(Bullet* const bullet)
{
	static int moveYDir = 1;
	bullet->Position.y += moveYDir * (bullet->Speed * FixedTimeDelta);

	if (bullet->Position.y >= MAP_HIGHT_SIZE)
	{
		bullet->IsViaild = false;
	}
}

void BulletMove(Bullet* const bullet)
{
	if (bullet->IsEmemy == true)
	{
		MonsterBulletMove(bullet);
	}
	else
	{
		PlayerBulletMove(bullet);
	}
}

void BulletHit(ENTITY* const entity, const Bullet* const bullet, const GRID_ITEM_TYPE gridType)
{
	switch (gridType)
	{
	case GRID_ITEM_TYPE::PLAYER:
		PlayerHit(entity, bullet->Att);
		break;
	case GRID_ITEM_TYPE::MONSTER:
		MonsterHit(entity, bullet, bullet->Att);
		break;
	default:
		break;
	}
}

bool BulletCollsion(const Bullet& const bullet, ENTITY** outEntity, GRID_ITEM_TYPE* outEntityType)
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

		// 몬스터 충돌처리
		ENTITY* entity = nullptr;
		GRID_ITEM_TYPE entityType;
		if (BulletCollsion(bullet, &entity, &entityType) == true)
		{
   			BulletHit(entity,  &bullet, entityType);

			bullet.IsViaild = false;
		}

		BulletMove(&bullet);
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

void CreateBullet(const vector2D<unsigned int> spawnPoint, const unsigned int attDamage, const BULLET_CREATOR_TYPE type)
{
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = _bullets[bulletIndex];

		if (bullet.IsViaild == false)
		{
			bullet.Position = CastingVector2D<double>(spawnPoint);
			bullet.Att = attDamage;
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
