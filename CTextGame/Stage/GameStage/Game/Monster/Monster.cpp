#include "Monster.h"

#include <Stage/GameStage/Game/Grid/Grid.h>
#include <Stage/GameStage/Game/Bullet/Bullet.h>
#include <Stage/GameStage/Game/Game.h>

#include <FrameRate/FrameRate.h>

#include <Renderer/Renderer.h>

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
        const MONSTER& monster = _monsters[monsterIndex];
        if (monster.Entity.IsVailed == true)
        {
            CopyDataToRendBuffer(CastingVector2D<unsigned int>(monster.Entity.Position), monster.Sprite);
        }
    }

    return 0;
}

bool CreateMonster(const MONSTER_FILE_INFO& monsterInfo, const STAGE_MONSTER_INFO& stageMonsterInfo)
{
    MONSTER* const monster = GetUnValiedMonster();

    // 이부분 깔끔하게 변경하면 좋을듯

    // entity
    monster->Entity.Hp = monsterInfo.Hp;
    monster->Entity.Att = monsterInfo.Att;
    monster->Entity.Speed = monsterInfo.Speed;
    monster->Entity.Position = stageMonsterInfo.Position;

    // move
    monster->MoveType = stageMonsterInfo.MoveType;

    // attack
    monster->FireCoolTime = monsterInfo.FireCoolTime;
    monster->FireCoolTimeRange = monsterInfo.FireCoolTimeRange;
    monster->LastFireTime = timeGetTime() + (rand() % monster->FireCoolTimeRange);

    // sprite
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
        MONSTER& monster = _monsters[monsterIndex];
        if (monster.Entity.IsVailed == true)
        {
            monster.Entity.IsVailed = false;
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

    const MONSTER* const pMonster = (MONSTER*)GetGridItem(CastingVector2D<int>(nextPosition), GRID_ITEM_TYPE::MONSTER);
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
    const vector2D<double> currentPoint = monster->Entity.Position;
    const vector2D<double> nextPoint = currentPoint + (monster->MoveDir * (monster->Entity.Speed * FixedDeltaTime));

    // 이동하려는 곳에 몬스터가 없음
    if (CanMove(monster, nextPoint) == true)
    {
        monster->Entity.Position = nextPoint;
        MoveGirdItem(CastingVector2D<int>(currentPoint), CastingVector2D<int>(nextPoint), GRID_ITEM_TYPE::MONSTER);
    }
    else
    {
        ReverseMoveDir(monster);
    }
}

void MonsterMoveType_2(MONSTER* const monster)
{
    const vector2D<double> currentPoint = monster->Entity.Position;

    // 다음 이동 방향 설정
    vector2D<double> moveDir = monster->MoveDir;

    // y축 랜덤
    if (rand() % 10 >= 4)
    {
        static short moveYDir[2] = { -1, 1 };
        const int randValue = rand() % 2;
        moveDir.y = moveYDir[randValue];
    }

    const vector2D<double> nextPoint = currentPoint + (moveDir * (monster->Entity.Speed * FixedDeltaTime));
    // 이동하려는 곳에 몬스터가 없음
    if (CanMove(monster, nextPoint) == true)
    {
        monster->Entity.Position = nextPoint;
        MoveGirdItem(CastingVector2D<int>(currentPoint), CastingVector2D<int>(nextPoint), GRID_ITEM_TYPE::MONSTER);
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
    static const int FireDegree = 90;
    static const vector2D<int> FireSpawnOffset = vector2D<int>{ 0, 1 };

    if (CanFire(monster) == true)
    {
        // create bullet
        const vector2D<unsigned int> bulletSpawnPoint = CastingVector2D<unsigned int>(monster->Entity.Position) + FireSpawnOffset;
        CreateBullet(bulletSpawnPoint, FireDegree, monster->Entity.Att, BULLET_CREATOR_TYPE::MONSTER);

        // fire cooltime
        monster->LastFireTime = timeGetTime() + (rand() % monster->FireCoolTimeRange);
    }
}