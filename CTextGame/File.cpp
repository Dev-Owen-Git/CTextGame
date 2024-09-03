#include "File.h"

#include "DataType.h"
#include "StringUtility.h"

#include <cstdio> 
#include <io.h>

#include <string>

// stage path
const char* _stage_file_path    = ".\\StageData\\Stage_%d.stage";
const char* _stageFindFilesPath = ".\\StageData\\*.stage";

// monster path
const char* _monster_file_path          = ".\\MonsterData\\Monster_%d.monster";
const char* _monsterFindFilesPath       = ".\\MonsterData\\*.monster";

// 폴더 내의 파일 전체 검사 후 갯수 반환
int FindAllStageFile(const char* folderPath)
{
    _finddata_t fd;
    intptr_t handle;
    int result = 1;

    handle = _findfirst(_stageFindFilesPath, &fd);

    if (handle == -1)
    {
        return false;
    }

    int count = 0;
    while (result != -1)
    {
        count++;
        result = _findnext(handle, &fd);
    }

    return count;
}


// STAGE FILE

// 스테이지 몬스터 값 가져오기
bool ParsingStageMonster(FILE* file, STAGE_FILE_INFO* stageInfo)
{
    char buffer[100];
    const char* pStr = fgets(buffer, sizeof(buffer), file);

    if (pStr == nullptr)
    {
        return false;
    }

    char outBuffer[10][10];
    if (StringSlice(pStr, outBuffer) == false)
    {
        return false;
    }
    
    // 파일 시작이 몬스터 인지 확인
    if (strcmp(outBuffer[0], "monster") != 0)
    {
        return false;
    }

    // 몬스터 몇 개 생성해야하는지 확인
    unsigned int monsterCount = atoi(outBuffer[1]);

    // { 추출
    pStr = fgets(buffer, sizeof(buffer), file);


    for (unsigned int i = 0; i < monsterCount; i++)
    {
        // id 추출
        pStr = fgets(buffer, sizeof(buffer), file);
        StringSlice(pStr, outBuffer);
        stageInfo->MonsterInfos[i].Id = atoi(outBuffer[2]);

        // pos 추출
        pStr = fgets(buffer, sizeof(buffer), file);
        StringSlice(pStr, outBuffer);
        stageInfo->MonsterInfos[i].Position.x = atoi(outBuffer[2]);
        stageInfo->MonsterInfos[i].Position.y = atoi(outBuffer[3]);

        // moveType 추출
        pStr = fgets(buffer, sizeof(buffer), file);
        StringSlice(pStr, outBuffer);
        stageInfo->MonsterInfos[i].MoveType = atoi(outBuffer[2]);

        stageInfo->MonsterInfos[i].isVailed = true;
    }

    // } 추출
    pStr = fgets(buffer, sizeof(buffer), file);
    
    return true;
}

// 스테이지 플레이어 위치 가져오기
bool ParsingStagePlayer(FILE* file, STAGE_FILE_INFO* stageInfo)
{
    char buffer[100];
    const char* pStr = fgets(buffer, sizeof(buffer), file);

    if (pStr == nullptr)
    {
        return false;
    }

    char outBuffer[10][10];
    if (StringSlice(pStr, outBuffer, "\n") == false)
    {
        return false;
    }

    // 파일 시작이 몬스터 인지 확인
    if (strcmp(outBuffer[0], "player") != 0)
    {
        return false;
    }

    // { 추출
    pStr = fgets(buffer, sizeof(buffer), file);

    // spawnPosition
    pStr = fgets(buffer, sizeof(buffer), file);
    StringSlice(pStr, outBuffer);
    stageInfo->PlayerSpawnPoint.x = (double)atoi(outBuffer[2]);
    stageInfo->PlayerSpawnPoint.y = (double)atoi(outBuffer[3]);


    // } 추출
    pStr = fgets(buffer, sizeof(buffer), file);
    return true;
}

// 스테이지 파일 파싱
bool ParsingStage(FILE* file, STAGE_FILE_INFO* stageInfo)
{
    if (ParsingStageMonster(file, stageInfo) == false)
    {
        return false;
    }

    if (ParsingStagePlayer(file, stageInfo) == false)
    {
        return false;
    }

    return true;
}

// 스테이지 파일 불러오기
bool LoadStageFiles(STAGE_FILE_INFO* stageInfo)
{
    int fileCount = FindAllStageFile(_stageFindFilesPath);
	for (int i = 0; i < fileCount; i++)
	{
		char filePath[128];
		sprintf_s(filePath, _stage_file_path, i);

        FILE* file;
        if (fopen_s(&file, filePath, "r") != 0)        // 0 == success
        {
            return false;
        }

        if (ParsingStage(file, &stageInfo[i]) == false)
        {
            fclose(file);
            return false;
        }
        stageInfo[i].isVailed = true;
		fclose(file);
	}
	return true;
}





// MONSTER FILE
bool ParsingMonster(FILE* file, MONSTER_FILE_INFO* monsterInfo)
{
    char outBuffer[10][100];
    char buffer[100];

    // att
    const char* pStr = fgets(buffer, sizeof(buffer), file);
    StringSlice(pStr, outBuffer);
    monsterInfo->Att = atoi(outBuffer[2]);

    // hp
    pStr = fgets(buffer, sizeof(buffer), file);
    StringSlice(pStr, outBuffer);
    monsterInfo->Hp = atoi(outBuffer[2]);

    // speed 추출
    pStr = fgets(buffer, sizeof(buffer), file);
    StringSlice(pStr, outBuffer);
    monsterInfo->Speed = atoi(outBuffer[2]);

    // fireCoolTime
    pStr = fgets(buffer, sizeof(buffer), file);
    StringSlice(pStr, outBuffer);
    monsterInfo->FireCoolTime = atoi(outBuffer[2]);
    monsterInfo->FireCoolTimeRange = atoi(outBuffer[3]);

    // sprtie
    pStr = fgets(buffer, sizeof(buffer), file);
    StringSlice(pStr, outBuffer);
    monsterInfo->Sprite = outBuffer[2][0];
   
    return true;
}

bool LoadMonsterFiles(MONSTER_FILE_INFO* monsterInfo)
{
    unsigned int fileCount = FindAllStageFile(_monsterFindFilesPath);
    for (unsigned int i = 0; i < fileCount; i++)
    {
        char filePath[128];
        sprintf_s(filePath, _monster_file_path, i);

        FILE* file;
        if (fopen_s(&file, filePath, "r") != 0)        // 0 == success
        {
            return false;
        }

        if (ParsingMonster(file, &monsterInfo[i]) == false)
        {
            fclose(file);
            return false;
        }

        fclose(file);
    }

    return true;
}
