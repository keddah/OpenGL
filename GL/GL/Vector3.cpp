/**************************************************************************************************************
* Vector3 - Code
*
* The code file for the Vector3 class. Gives functionality to operators like   += ... *=    as well as
* Creates functions that are used to compare the distances of the 2 Vector2's.
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Vector3.h"

#include <random>

Vector3::Vector3()
{
	x = y = z = 0;
}

Vector3::Vector3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3 Vector3::operator*=(const float multiplier)
{
	x *= multiplier;
	y *= multiplier;
	z *= multiplier;

	return *this;
}

Vector3 Vector3::operator/=(const float divider)
{
	x /= divider;
	y /= divider;
	z /= divider;

	return *this;
}

bool Vector3::Compare(const Vector3& other, const float tolerance = 1) const
{
	const bool equal_x = (x >= static_cast<float>(other.x) + tolerance || static_cast<float>(other.x) >= x + tolerance) ||
		x >= static_cast<float>(other.x) - tolerance || static_cast<float>(other.x) >= x - tolerance;

	const bool equal_y = (y >= static_cast<float>(other.y) + tolerance || static_cast<float>(other.y) >= y + tolerance) ||
		y >= static_cast<float>(other.y) - tolerance || static_cast<float>(other.y) >= y - tolerance;

	const bool equal_z = (z >= static_cast<float>(other.z) + tolerance || static_cast<float>(other.z) >= z + tolerance) ||
		z >= static_cast<float>(other.z) - tolerance || static_cast<float>(other.z) >= z - tolerance;

	return  equal_x && equal_y && equal_z;
}

// Used this to check collisions since it was more reliable
float Vector3::Distance(const Vector3& other) const
{
	const float difference_x = x - other.x;
	const float difference_y = y - other.y;
	const float difference_z = z - other.z;

	// The magnitude of the difference = the distance between the 2 points
	const float distance = Vector3(difference_x, difference_y, difference_z).Magnitude();
	return distance;
}

float Vector3::FindLookRotation(Vector3 start, Vector3 target)
{
	// Rotate towards the direction it's going in.
	const Vector3 difference = start - target;
	// 2d ATM
	const float rotation = (atan2(difference.y, difference.x)) * 180 / std::_Pi;
	return rotation;
}
