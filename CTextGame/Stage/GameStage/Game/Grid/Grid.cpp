#include "Grid.h"

#include <memory>

#include <Stage/GameStage/Game/Player/Player.h>
#include <Stage/GameStage/Game/Monster/Monster.h>

GRID Grid[MAP_HIGHT_SIZE][MAP_WITDH_SIZE];

bool GridInit()
{
	::memset(Grid, 0, sizeof(Grid));
	return true;
}

void SetGridItem(const vector2D<int> gridPosition, const void* const item, const GRID_ITEM_TYPE type)
{
	switch (type)
	{
	case GRID_ITEM_TYPE::MONSTER:
		Grid[gridPosition.y][gridPosition.x].Monster = (MONSTER*)item;
		break;
	case GRID_ITEM_TYPE::PLAYER:
		Grid[gridPosition.y][gridPosition.x].Player = (PLAYER*)item;
		break;
	default:
		break;
	}
}

void RemoveGridItem(const vector2D<int> gridPosition, const GRID_ITEM_TYPE type)
{
	SetGridItem(gridPosition, nullptr, type);
}

void MoveGirdItem(const vector2D<int> oldPosition, const vector2D<int> nowPosition, const GRID_ITEM_TYPE type)
{
	if (oldPosition.x == nowPosition.x && oldPosition.y == nowPosition.y)
	{
		return;
	}

	auto& nowGrid = Grid[nowPosition.y][nowPosition.x];
	auto& oldGrid = Grid[oldPosition.y][oldPosition.x];

	switch (type)
	{
	case GRID_ITEM_TYPE::MONSTER:
		nowGrid.Monster = oldGrid.Monster;
		oldGrid.Monster = nullptr;
		break;
	case GRID_ITEM_TYPE::PLAYER:
		nowGrid.Player = oldGrid.Player;
		oldGrid.Player = nullptr;
		break;
	default:
		break;
	}
}

void* GetGridItem(const vector2D<int>& src, const GRID_ITEM_TYPE type)
{
	switch (type)
	{
	case GRID_ITEM_TYPE::MONSTER:
		return Grid[src.y][src.x].Monster;
	case GRID_ITEM_TYPE::PLAYER:
		return Grid[src.y][src.x].Player;
	default:
		break;
	}

	return nullptr;
}
