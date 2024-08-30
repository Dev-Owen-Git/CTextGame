#pragma once

template<typename T>
struct vector2D
{
	T x, y;
};

template<typename T1, typename T2>
vector2D<T1>  CastingVector2D(vector2D<T2> srcVector2D)
{
	vector2D<T1> vector = { (T1)srcVector2D.x, (T1)srcVector2D.y };
	return vector;
}


static const int RENDER_BUFFER_WIDTH_SIZE = 70;
static const int RENDER_BUFFER_HEIGHT_SIZE = 30;

static const int MAP_WITDH_SIZE = 40;
static const int MAP_HIGHT_SIZE = 30;

static const int MAX_CAN_USE_BUFFER_SIZE = MAP_WITDH_SIZE - 1;

static const int MAX_STAGE_MONSTER_COUNT = 30;
static const int MAX_MONSTER_TYPE = 10;