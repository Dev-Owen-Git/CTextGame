#include "Utility.h"

bool Colision(const uvector2& src, const uvector2& dest)
{
	if (src.x == dest.x && src.y && dest.y)
		return true;

	return false;
}
