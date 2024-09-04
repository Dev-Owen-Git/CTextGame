#include "Entity.h"



void InitEntity(ENTITY* const entity, const unsigned int hp, const unsigned att, const double speed, const vector2D<double> position)
{
	entity->Hp = hp;
	entity->Att = att;
	entity->Speed = speed;
	entity->Position = position;
	entity->IsVailed = true;
}

// entity가 unvailed 되면서 grid에서 제거
void EntityUnVailed(ENTITY* const entity, const bool removeToGrid, const GRID_ITEM_TYPE girdItemType)
{
	entity->IsVailed = false;

	if (removeToGrid == true)
	{
		RemoveGridItem(CastingVector2D<int>(entity->Position), girdItemType);
	}
}

void EntityHit(ENTITY* const entity, const int damage, void(*entityDeadCallBack)(ENTITY* const))
{
	entity->Hp -= damage;

	if (entity->Hp <= 0)
	{
		entityDeadCallBack(entity);
	}
}
