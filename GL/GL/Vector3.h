/**************************************************************************************************************
* Vector3 - Header
*
* The header file for the Vector2 class. Allows math operators to be applied to Vectors accordingly.
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/
#define print(x){std::cout << (x) << std::endl;}

#pragma once
#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(float X, float Y, float Z);

	float x, y, z;

	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);
	Vector3 operator*=(const float multiplier);
	Vector3 operator/=(const float divider);

	Vector3 operator+(const Vector3& other) const
	{
		return { x + other.x, y + other.y, z + other.z};
	}

	Vector3 operator-(const Vector3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	Vector3 operator*(const float multiplier) const
	{

		return { x * multiplier, y * multiplier, z * multiplier };
	}
	Vector3 operator/(const float divider) const
	{
		return { x / divider, y / divider, z / divider };
	}

	bool operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vector3& other) const
	{
		return x != other.x || y != other.y || z != other.z ;
	}

	bool Compare(const Vector3& other, float tolerance) const;
	float Magnitude() const { return sqrt((x * x) + (y * y) + (z * z)); }
	float Distance(const Vector3& other) const;

	static float FindLookRotation(Vector3 start, Vector3 target);
};
