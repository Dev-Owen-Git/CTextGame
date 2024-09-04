#pragma once

#include <Data/Vector2D/Vector2D.h>
#include <Stage/GameStage/Game/Grid/Grid.h>

struct ENTITY
{
	bool IsVailed = false;

	int Hp;
	unsigned int Att;
	double Speed;

	vector2D<double> Position;
};

void InitEntity(ENTITY* const entity, const unsigned int hp, const unsigned att, const double speed, const vector2D<double> position);
void EntityUnVailed( ENTITY* const entity, const bool removeToGrid, const GRID_ITEM_TYPE girdItemType);
void EntityHit(ENTITY* const entity, const int damage, void(*entityDeadCallBack)(ENTITY* const));