#pragma once

#include <Data/GlobalData.h>
#include <Data/Vector2D/Vector2D.h>

enum class GRID_ITEM_TYPE
{
	MONSTER,
	PLAYER,
};

struct GRID
{
	struct MONSTER*	Monster	= nullptr;
	struct PLAYER*	Player	= nullptr;
};


extern GRID Grid[MAP_HIGHT_SIZE][MAP_WITDH_SIZE];

bool GridInit();

void SetGridItem(const vector2D<int> gridPosition, const void* const item, const GRID_ITEM_TYPE type);
void RemoveGridItem(const vector2D<int> gridPosition, const GRID_ITEM_TYPE type);
void MoveGirdItem(const vector2D<int> currentPosition, const vector2D<int> nextPosition, const GRID_ITEM_TYPE type);

void* GetGridItem(const vector2D<int>& src, const GRID_ITEM_TYPE type);