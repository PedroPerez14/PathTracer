
/*
 * Author: Pedro José Pérez García
 * Date: 20/07/2021
 * Coms: Tipo de dato que va a representar una textura + funciones para leerla
 */
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Vector3.h"

using namespace std;

struct Texture
{
	float u_left;
	float u_right;
	float v_up;
	float v_down;
	int width;
	int height;
	float max = 1.0f;			//En caso de fallo, mirar aquí, es sus, antes tenía 255.0f
	float c;
	vector<Color> texels;

	Color get_texel(const float& u, const float& v) const
	{
		int width_ret = abs(fmod((u - u_left) / (u_right - u_left), 1)) * width;
		int height_ret = abs(fmod((v - v_up) / (v_down - v_up), 1)) * height;
		return texels[width_ret + height_ret * width];
	}
};

string read_line_(ifstream& in);

shared_ptr<Texture> read_tex_from_file(std::string file, float u_left, float u_right, float v_up, float v_down);