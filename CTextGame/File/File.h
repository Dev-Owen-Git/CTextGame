#pragma once

#include <Data/Vector2D/Vector2D.h>
#include <Data/GlobalData.h>

struct STAGE_MONSTER_INFO
{
    bool isVailed = false;

    unsigned int Id;

    vector2D<double> Position;
    unsigned int MoveType;
};


struct STAGE_FILE_INFO
{
    bool isVailed = false;

    STAGE_MONSTER_INFO  MonsterInfos[MAX_STAGE_MONSTER_COUNT];
    vector2D<double>	PlayerSpawnPoint;
};

const int MAX_STAGE_COUNT = 10;


struct MONSTER_FILE_INFO
{
    // entity
    unsigned int Hp;
    unsigned int Att;
    unsigned int Speed;

    // Attack
    unsigned int FireCoolTime;
    unsigned int FireCoolTimeRange;

    // Img
    unsigned char Sprite;
};

bool LoadStageFiles(STAGE_FILE_INFO* stageInfo);
bool LoadMonsterFiles(MONSTER_FILE_INFO* monsterInfo);