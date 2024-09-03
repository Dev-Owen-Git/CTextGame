#include "Monster.h"

#include "Renderer.h"
#include "Grid.h"
#include "Bullet.h"
#include "Game.h"
#include "FrameRate.h"

#include <Windows.h>

const int MAX_CAN_MOVE_HEIGHT = 5;

MONSTER _monsters[MAX_STAGE_MONSTER_COUNT];

unsigned int AliveMonsterCount = 0;

// move
bool CanMove(const MONSTER* const monster, const vector2D<double> nextPosition);
void MonsterMove(MONSTER* const monster);
void MonsterMoveType_1(MONSTER* const monster);
void MonsterMoveType_2(MONSTER* const monster);
void ReverseMoveDir(MONSTER* const monster);

// fire
bool CanFire(const MONSTER* const monster);
void MonsterFire(MONSTER* const monster);

bool MonsterInit()
{
    ClearAllMonsters();
    return true;
}

int MonsterProcess()
{
    for (unsigned short monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        MONSTER& monster = _monsters[monsterIndex];
        if (monster.Entity.IsVailed == true)
        {
            MonsterMove(&monster);
            MonsterFire(&monster);
        }
    }
    return 0;
}

int MonsterRender()
{
    for (unsigned short monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        MONSTER* monster = &_monsters[monsterIndex];
        if (monster->Entity.IsVailed == true)
        {
            CopyDataToRendBuffer(CastingVector2D<unsigned int>(monster->Entity.Position), monster->Sprite);
        }
    }

    return 0;
}

bool CreateMonster(const MONSTER_FILE_INFO& monsterInfo, const STAGE_MONSTER_INFO& stageMonsterInfo)
{
    MONSTER* monster = GetUnValiedMonster();
    monster->Entity.Position = stageMonsterInfo.Position;
    monster->Entity.Hp = monsterInfo.Hp;
    monster->Entity.Att = monsterInfo.Att;
    monster->Entity.Speed = monsterInfo.Speed;

    monster->FireCoolTime = monsterInfo.FireCoolTime;
    monster->FireCoolTimeRange = monsterInfo.FireCoolTimeRange;
    monster->LastFireTime = timeGetTime() + (rand() % monster->FireCoolTimeRange);

    monster->MoveType = stageMonsterInfo.MoveType;
    monster->Sprite = monsterInfo.Sprite;

    SetGridItem(CastingVector2D<int>(monster->Entity.Position), &monster->Entity, GRID_ITEM_TYPE::MONSTER);

    monster->Entity.IsVailed = true;
    AliveMonsterCount++;

    return monster->Entity.IsVailed;
}

void ClearAllMonsters()
{
    for (int monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        MONSTER* monster = &_monsters[monsterIndex];
        if (monster->Entity.IsVailed == true)
        {
            monster->Entity.IsVailed = false;
        }
    }

    AliveMonsterCount = 0;
}


void MonsterHit(ENTITY* const entity, const int damage)
{
    entity->Hp -= damage;

    if (entity->Hp <= 0)
    {
        entity->IsVailed = false;

        AliveMonsterCount--;
        RemoveGridItem(CastingVector2D<int>(entity->Position), GRID_ITEM_TYPE::MONSTER);
    }

    if (AliveMonsterCount <= 0)
    {
        NetGameStage();
    }
}

MONSTER* GetUnValiedMonster()
{
    for (unsigned short monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        if (_monsters[monsterIndex].Entity.IsVailed == false)
        {
            return &_monsters[monsterIndex];
        }
    }

    return nullptr;
}












// MONSTER MOVE //
bool CanMove(const MONSTER* const monster, const vector2D<double> nextPosition)
{
    // gird에 이동가능 여부 추가하기
    if (nextPosition.x < 0 || nextPosition.x >= MAP_WITDH_SIZE || nextPosition.y < 0 || nextPosition.y >= MAX_CAN_MOVE_HEIGHT)
    {
        return false;
    }

    MONSTER* pMonster = (MONSTER*)GetGridItem(CastingVector2D<int>(nextPosition), GRID_ITEM_TYPE::MONSTER);
    if (pMonster == nullptr || pMonster == monster)
    {
        return true;
    }

    return false;
}

void MonsterMove(MONSTER* const monster)
{
    switch (monster->MoveType)
    {
    case 0:
        MonsterMoveType_1(monster);
        break;
    case 1:
        MonsterMoveType_2(monster);
        break;
    default:
        break;
    }
}

void MonsterMoveType_1(MONSTER* const monster)
{
    vector2D<double> currentPosition = monster->Entity.Position;

    vector2D<double> nextPosition = currentPosition;
    nextPosition.x += monster->MoveDir.x * (monster->Entity.Speed * FixedDeltaTime);

    // 이동하려는 곳에 몬스터가 없음
    if (CanMove(monster, nextPosition) == true)
    {
        monster->Entity.Position = nextPosition;
        MoveGirdItem(CastingVector2D<int>(currentPosition), CastingVector2D<int>(nextPosition), GRID_ITEM_TYPE::MONSTER);
    }
    else
    {
        ReverseMoveDir(monster);
    }
}

void MonsterMoveType_2(MONSTER* const monster)
{
    vector2D currentPosition = monster->Entity.Position;

    vector2D nextPosition = currentPosition;
    nextPosition.x += monster->MoveDir.x * (monster->Entity.Speed * FixedDeltaTime);


    if (rand() % 10 >= 4)
    {
        static short moveYDir[2] = { -1, 1 };
        auto randValue = (rand() % 2);
        nextPosition.y += moveYDir[randValue] * (monster->Entity.Speed * FixedDeltaTime);
    }

    // 이동하려는 곳에 몬스터가 없음
    if (CanMove(monster, nextPosition) == true)
    {
        monster->Entity.Position = nextPosition;
        MoveGirdItem(CastingVector2D<int>(currentPosition), CastingVector2D<int>(nextPosition), GRID_ITEM_TYPE::MONSTER);
    }
    else
    {
        ReverseMoveDir(monster);
    }
}

void ReverseMoveDir(MONSTER* const monster)
{
    monster->MoveDir.x *= -1;
    monster->MoveDir.y *= -1;
}






















// MONSTER ATTACK
bool CanFire(const MONSTER* const monster)
{
    if (monster->LastFireTime + monster->FireCoolTime <= timeGetTime())
    {
        return true;
    }
    return false;
}

void MonsterFire(MONSTER* const monster)
{
    if (CanFire(monster) == true)
    {
        vector2D<unsigned int> bulletSpawnPoint = CastingVector2D<unsigned int>(monster->Entity.Position);
        bulletSpawnPoint.y += 1;

        CreateBullet(bulletSpawnPoint, 270, monster->Entity.Att, BULLET_CREATOR_TYPE::MONSTER);

        monster->LastFireTime = timeGetTime() + (rand() % monster->FireCoolTimeRange);
    }
}