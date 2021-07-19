/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: x y z , r g b , ahora son lo mismo
 */

#pragma once
#include <string>

typedef struct Vector3
{
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };

	float mod() const 
	{
		return sqrtf(x * x + y * y + z * z);
	}

	void normalize()
	{
		float modulus = this->mod();
		x /= modulus;
		y /= modulus;
		z /= modulus;
	}

	std::string to_string() const
	{
		return "[ " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "]";
	}

	Vector3 operator-(Vector3 v) const 
	{
		return Vector3{x - v.x, y - v.y, z - v.z};
	}

	Vector3 operator+(Vector3 v) const
	{
		return Vector3{ x + v.x, y + v.y, z + v.z };
	}

	Vector3 operator*(const float& scalar) const
	{
		return Vector3{ x * scalar, y * scalar, z * scalar };
	}

	bool operator==(const Vector3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}
	
	bool operator!=(const Vector3& v) const
	{
		return (x != v.x || y != v.y || z != v.z);
	}

	Vector3 perpendicular() const	//Returns a perpendicular vector to the one given
	{
		if (x == 0)
		{
			return Vector3{ 0, -z, y };
		}
		else
		{
			return Vector3{ -y, x, 0 };
		}
	}

}Vector3;
typedef Vector3 Color;

float dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3{ v1.y * v2.z - v1.z * v2.y, -(v1.x * v2.z - v1.z * v2.x), v1.x * v2.y - v1.y * v2.x };
}

float angle(const Vector3& v1, const Vector3& v2)
{
	float cos = dot(v1, v2) / v1.mod() / v2.mod();
	return acos(cos);
}


