#include "File.h"

#include <stdio.h>

#include <cstdio> 
#include <iostream>
#include <io.h>
#include <fstream>
#include <sstream>

const char* MONSTER_FILE_PATH = "..\\Monsters\\MonsterInfo%c.monsterData";
const char* _findFilesPath = ".\\Monsters\\*.monsterData";


int AllFineFile()
{
    _finddata_t fd;
    intptr_t handle;
    int result = 1;

    handle = _findfirst(_findFilesPath, &fd);

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

bool ReadMonsteerFile(void* outData, const int dataSize)
{
	// 스테이지 갯 수

    int fileCount = AllFineFile();
	for (int i = 0; i < fileCount; i++)
	{
		char filePath[128];
		sprintf(filePath, MONSTER_FILE_PATH, i);

		auto file = fopen(MONSTER_FILE_PATH, "w");

		if (file == nullptr)
		{
			return false;
		}

		fclose(file);
	}
	return true;
}
