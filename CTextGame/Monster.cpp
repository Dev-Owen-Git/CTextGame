#include "Monster.h"

#include "Renderer.h"
#include "Grid.h"
#include "Bullet.h"
#include "Game.h"
#include "FrameRate.h"

#include <Windows.h>

MONSTER Monsters[MAX_STAGE_MONSTER_COUNT];

unsigned int AliveMonsterCount = 0;

void ReverseMoveDir(MONSTER* monster)
{
    monster->MoveDir.x *= -1;
    monster->MoveDir.y *= -1;
}

bool CanMove(const MONSTER* monster, vector2D<double> nextPosition)
{
    if (nextPosition.x < 0 || nextPosition.x >= MAP_WITDH_SIZE - 1 || nextPosition.y < 0 || nextPosition.y >= 5)
    {
        return false;
    }

    MONSTER* pMonster = (MONSTER*)GetGridItem(CastingVector2D<int>(nextPosition), GRID_ITEM_TYPE::MONSTER);
    if (monster == pMonster || pMonster == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }

    return true;
}

void MonsterMoveType_1(MONSTER* monster)
{
    vector2D<double> currentPosition = monster->Entity.Position;

    vector2D<double> nextPosition = currentPosition;
    nextPosition.x += monster->MoveDir.x * (monster->Entity.Speed * FixedTimeDelta);

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

void MonsterMoveType_2(MONSTER* monster)
{
    vector2D currentPosition = monster->Entity.Position;

    vector2D nextPosition = currentPosition;
    nextPosition.x += monster->MoveDir.x * (monster->Entity.Speed * FixedTimeDelta);


    if (rand() % 10 >= 4)
    {
        static short moveYDir[2] = { -1, 1 };
        auto randValue = (rand() % 2);
        nextPosition.y += moveYDir[randValue] * (monster->Entity.Speed * FixedTimeDelta);
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

void MonsterMove(MONSTER* monster)
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


bool CreateMonster(const MONSTER_FILE_INFO& const  monsterInfo, const STAGE_MONSTER_INFO& const stageMonsterInfo)
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
        MONSTER* monster = &Monsters[monsterIndex];
        if (monster->Entity.IsVailed == true)
        {
            monster->Entity.IsVailed = false;
        }
    }
}

bool MonsterInit()
{
    ClearAllMonsters();
    AliveMonsterCount = 0;

    return true;
}

bool CanFire(const MONSTER& monster)
{
    if (monster.LastFireTime + monster.FireCoolTime <= timeGetTime())
    {
        return true;
    }
    return false;
}

void MonsterFire(unsigned short monsterIndex)
{
    auto& monster = Monsters[monsterIndex];
    if (CanFire(monster) == true)
    {
        vector2D<unsigned int> bulletSpawnPoint = CastingVector2D<unsigned int>(monster.Entity.Position);
        bulletSpawnPoint.y += 1;

        CreateBullet(bulletSpawnPoint, monster.Entity.Att, BULLET_CREATOR_TYPE::MONSTER);

        monster.LastFireTime = timeGetTime() + (rand() % monster.FireCoolTimeRange);
    }
}

int MonsterProcess()
{
    for (unsigned short monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        MONSTER* monster = &Monsters[monsterIndex];
        if (monster->Entity.IsVailed == true)
        {
            MonsterMove(monster);
            MonsterFire(monsterIndex);
        }
    }
    return 0;
}

int MonsterRender()
{
    for (unsigned short monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        MONSTER* monster = &Monsters[monsterIndex];
        if (monster->Entity.IsVailed == true)
        {
            CopyDataToRendBuffer(CastingVector2D<unsigned int>(monster->Entity.Position), monster->Sprite);
        }
    }

    return 0;
}

void MonsterHit(ENTITY* const entity, const Bullet* const bullet, const int damage)
{
    entity->Hp -= damage;

    if (entity->Hp <= 0)
    {
        entity->IsVailed = false;

        AliveMonsterCount--;

        RemoveGridItem(CastingVector2D<int>(entity->Position), GRID_ITEM_TYPE::MONSTER);
    }

    if (AliveMonsterCount == 0)
    {
        NetGameStage();
    }
}

MONSTER* GetUnValiedMonster()
{
    for (unsigned short monsterIndex = 0; monsterIndex < MAX_STAGE_MONSTER_COUNT; monsterIndex++)
    {
        if (Monsters[monsterIndex].Entity.IsVailed == false)
        {
            return &Monsters[monsterIndex];
        }
    }

    return nullptr;
}