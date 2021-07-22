/*
 * Author: Pedro José Pérez García
 * Date: 22/07/2021
 * Coms: Transformaciones a Vectores, como cambios de base + tipo Matrix para transformar (tam. 4x4)
 */

#pragma once
#include "../DataTypes/Vector3.h"

struct Matrix
{
	float m[4][4];

	Vector3 operator*(const Vector3& vec)
	{
		float v[4] = {vec.x, vec.y, vec.z, 1.0f};
		float ret[4];
		for (int i = 0; i < 4; i++)
		{
			ret[i] = 0;
			for (int j = 0; j < 4; j++)
			{
				ret[i] += m[i][j] * v[j];
			}
		}
		return Vector3{ ret[0], ret[1] , ret[2] };
	}
};

Matrix base_change_matrix(Vector3 b1, Vector3 b2, Vector3 b3, Vector3 origin);

Matrix invert(const Matrix& M);

Vector3 change_coord_system_point(Vector3 v, Vector3 b1, Vector3 b2, Vector3 b3, Vector3 origin = Vector3{ 0, 0, 0 });

Vector3 change_coord_system_dir(Vector3 v, Vector3 b1, Vector3 b2, Vector3 b3, Vector3 origin = Vector3{ 0, 0, 0 });

Vector3 mult_dir(Matrix m, Vector3 vec);
