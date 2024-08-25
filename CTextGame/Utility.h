#pragma once

struct uvector2
{
	unsigned int x, y;
};

static const int MAP_HIGHT_SIZE = 30;
static const int MAP_WITDH_SIZE = 40;

bool Colision(const uvector2& src, const uvector2& dest);