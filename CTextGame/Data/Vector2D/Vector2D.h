#pragma once

template<typename T>
struct vector2D
{
	T x, y;
};

template<typename Type1, typename Type2>
vector2D<Type1> operator*(vector2D<Type1> vectorValue, const Type2 value)
{
	vectorValue.x *= value;
	vectorValue.y *= value;

	return vectorValue;
}

template<typename Type1, typename Type2>
vector2D<Type1> operator+(vector2D<Type1> srcValue, const vector2D<Type2> destValue)
{
	srcValue.x += destValue.x;
	srcValue.y += destValue.y;

	return srcValue;
}

template<typename Type1, typename Type2>
vector2D<Type1> operator+=(vector2D<Type1>& srcValue, const vector2D<Type2>& destValue)
{
	srcValue.x += destValue.x;
	srcValue.y += destValue.y;

	return srcValue;
}

template<typename T1, typename T2>
vector2D<T1>  CastingVector2D(vector2D<T2> srcVector2D)
{
	vector2D<T1> vector = { (T1)srcVector2D.x, (T1)srcVector2D.y };
	return vector;
}