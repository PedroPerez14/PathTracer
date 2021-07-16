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
