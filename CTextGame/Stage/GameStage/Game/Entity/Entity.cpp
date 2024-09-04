#include "Entity.h"

void InitEntity(ENTITY* const entity, const unsigned int hp, const unsigned att, const double speed, const vector2D<double> position)
{
	entity->Hp = hp;
	entity->Att = att;
	entity->Position = position;
	entity->Speed = speed;
	entity->IsVailed = true;
}
