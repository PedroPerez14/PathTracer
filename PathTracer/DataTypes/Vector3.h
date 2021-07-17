/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: x y z , r g b , ahora son lo mismo
 */

#pragma once

typedef struct Vector3
{
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };
}Vector3;
typedef Vector3 Color;

float mod(const Vector3& vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

void normalize(Vector3& vec)
{
	float modulus = mod(vec);
	vec.x /= modulus;
	vec.y /= modulus;
	vec.z /= modulus;
}
std::string to_string(const Vector3& vec)
{
	return "[ " + std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z) + "]";
}