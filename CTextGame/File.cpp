#include "File.h"

#include "utility.h"
#include "StringUtility.h"

#include <cstdio> 
#include <io.h>

#include <string>

// stage path
const char* _stage_file_path = ".\\StageData\\Stage_%d.stage";
const char* _stageFindFilesPath = ".\\StageData\\*.stage";

// monster path
const char* _monster_file_path          = ".\\Monsters\\MonsterInfo%c.monsterData";
const char* _monsterFindFilesPath      = ".\\Monsters\\*.monsterData";


int FindAllStageFile()
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

bool IsStageFile(FILE* file)
{
    char buffer[100];
    const char* pStr = fgets(buffer, 100, file);

    if (pStr == nullptr)
    {
        return false;
    }

    char outBuffer[10][10];
    StringSlice(pStr, outBuffer);

    if (strcmp(outBuffer[0], "monster") == 0)
    {
        return true;
    }
    
    return false;
}

bool ParsingStage(FILE* file)
{
    if (IsStageFile(file) == false)
    {
        return false;
    }

    

    return false;
}

bool LoadStage(void* outData, const int dataSize)
{
	// 스테이지 갯 수

    // TODO 파일 이름 불러오기
    // TODO 몬스터 이동 만들기

    int fileCount = FindAllStageFile();
	for (int i = 1; i <= fileCount; i++)
	{
		char filePath[128];
		sprintf_s(filePath, _stage_file_path, i);

        FILE* file;
        if (fopen_s(&file, filePath, "r") != 0)        // 0 == success
        {
            return false;
        }

        if (ParsingStage(file) == true)
        {

        }

		fclose(file);
	}
	return true;
}
