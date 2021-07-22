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

Matrix base_change_matrix(Vector3 b1, Vector3 b2, Vector3 b3, Vector3 origin) {
	float aux[4][4] = {
			{ b1.x, b2.x, b3.x, origin.x },
			{ b1.y, b2.y, b3.y, origin.y },
			{ b1.z, b2.z, b3.z, origin.z },
			{0.0f, 0.0f, 0.0f, 1.0f}
	};
	Matrix ret{};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret.m[i][j] = aux[i][j];
		}
	}
	return ret;
}

Matrix invert(const Matrix& M)
{
    Matrix ret;
    float a00 = M.m[0][0]; float a01 = M.m[0][1]; float a02 = M.m[0][2]; float a03 = M.m[0][3];
    float a10 = M.m[1][0]; float a11 = M.m[1][1]; float a12 = M.m[1][2]; float a13 = M.m[1][3];
    float a20 = M.m[2][0]; float a21 = M.m[2][1]; float a22 = M.m[2][2]; float a23 = M.m[2][3];
    float a30 = M.m[3][0]; float a31 = M.m[3][1]; float a32 = M.m[3][2]; float a33 = M.m[3][3];

    ret.m[0][0] = a11 * a22 * a33 - a11 * a23 * a32 - a21 * a12 * a33 + a21 * a13 * a32 + a31 * a12 * a23 - a31 * a13 * a22;
    ret.m[0][1] = -a01 * a22 * a33 + a01 * a23 * a32 + a21 * a02 * a33 - a21 * a03 * a32 - a31 * a02 * a23 + a31 * a03 * a22;
    ret.m[0][2] = a01 * a12 * a33 - a01 * a13 * a32 - a11 * a02 * a33 + a11 * a03 * a32 + a31 * a02 * a13 - a31 * a03 * a12;
    ret.m[0][3] = -a01 * a12 * a23 + a01 * a13 * a22 + a11 * a02 * a23 - a11 * a03 * a22 - a21 * a02 * a13 + a21 * a03 * a12;
    ret.m[1][0] = -a10 * a22 * a33 + a10 * a23 * a32 + a20 * a12 * a33 - a20 * a13 * a32 - a30 * a12 * a23 + a30 * a13 * a22;
    ret.m[1][1] = a00 * a22 * a33 - a00 * a23 * a32 - a20 * a02 * a33 + a20 * a03 * a32 + a30 * a02 * a23 - a30 * a03 * a22;
    ret.m[1][2] = -a00 * a12 * a33 + a00 * a13 * a32 + a10 * a02 * a33 - a10 * a03 * a32 - a30 * a02 * a13 + a30 * a03 * a12;
    ret.m[1][3] = a00 * a12 * a23 - a00 * a13 * a22 - a10 * a02 * a23 + a10 * a03 * a22 + a20 * a02 * a13 - a20 * a03 * a12;
    ret.m[2][0] = a10 * a21 * a33 - a10 * a23 * a31 - a20 * a11 * a33 + a20 * a13 * a31 + a30 * a11 * a23 - a30 * a13 * a21;
    ret.m[2][1] = -a00 * a21 * a33 + a00 * a23 * a31 + a20 * a01 * a33 - a20 * a03 * a31 - a30 * a01 * a23 + a30 * a03 * a21;
    ret.m[2][2] = a00 * a11 * a33 - a00 * a13 * a31 - a10 * a01 * a33 + a10 * a03 * a31 + a30 * a01 * a13 - a30 * a03 * a11;
    ret.m[2][3] = -a00 * a11 * a23 + a00 * a13 * a21 + a10 * a01 * a23 - a10 * a03 * a21 - a20 * a01 * a13 + a20 * a03 * a11;
    ret.m[3][0] = -a10 * a21 * a32 + a10 * a22 * a31 + a20 * a11 * a32 - a20 * a12 * a31 - a30 * a11 * a22 + a30 * a12 * a21;
    ret.m[3][1] = a00 * a21 * a32 - a00 * a22 * a31 - a20 * a01 * a32 + a20 * a02 * a31 + a30 * a01 * a22 - a30 * a02 * a21;
    ret.m[3][2] = -a00 * a11 * a32 + a00 * a12 * a31 + a10 * a01 * a32 - a10 * a02 * a31 - a30 * a01 * a12 + a30 * a02 * a11;
    ret.m[3][3] = a00 * a11 * a22 - a00 * a12 * a21 - a10 * a01 * a22 + a10 * a02 * a21 + a20 * a01 * a12 - a20 * a02 * a11;

    float D = (
        a00 * a11 * a22 * a33 - a00 * a11 * a23 * a32 - a00 * a21 * a12 * a33 + a00 * a21 * a13 * a32 + a00 * a31 * a12 * a23 - a00 * a31 * a13 * a22
        - a10 * a01 * a22 * a33 + a10 * a01 * a23 * a32 + a10 * a21 * a02 * a33 - a10 * a21 * a03 * a32 - a10 * a31 * a02 * a23 + a10 * a31 * a03 * a22
        + a20 * a01 * a12 * a33 - a20 * a01 * a13 * a32 - a20 * a11 * a02 * a33 + a20 * a11 * a03 * a32 + a20 * a31 * a02 * a13 - a20 * a31 * a03 * a12
        - a30 * a01 * a12 * a23 + a30 * a01 * a13 * a22 + a30 * a11 * a02 * a23 - a30 * a11 * a03 * a22 - a30 * a21 * a02 * a13 + a30 * a21 * a03 * a12
        );

    if (D) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret.m[i][j] /= D;
            }
        }
    }
    else {
        cerr << "WARNING: Matrix has no inverse!" << endl;
    }
    return ret;
}

Vector3 change_coord_system(Vector3 v, Vector3 b1, Vector3 b2, Vector3 b3, Vector3 origin)
{
	Matrix m = base_change_matrix(b1, b2, b3, origin);
	m = invert(m);
	return m * v;
}