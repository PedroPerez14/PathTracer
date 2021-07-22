/*
 * Author: Pedro José Pérez García
 * Date: 22/07/2021
 * Coms: Tengo que separar declaraciones e implementaciones
 */
#pragma once
#include "Texture.h"

string read_line_(ifstream& in)
{
	string ret;
	bool end = false;
	while (!end)
	{
		in >> ret;
		if (ret[0] == '#')
		{
			if (ret.substr(0, 5) == "#MAX=")
			{
				ret = ret.substr(5);
				end = true;
			}
			else
			{
				getline(in, ret);
			}
		}
		else
		{
			end = true;
		}
	}
	return ret;
}

shared_ptr<Texture> read_tex_from_file(std::string file, float u_left, float u_right, float v_up, float v_down)
{
	Texture tex{};
	string kk, lec;
	float r, g, b;

	tex.u_left = u_left;
	tex.u_right = u_right;
	tex.v_up = v_up;
	tex.v_down = v_down;

	ifstream in;
	in.open(file);

	//read header
	kk = read_line_(in);
	lec = read_line_(in);
	tex.width = stoi(lec);
	lec = read_line_(in);
	tex.height = stoi(lec);
	lec = read_line_(in);
	tex.c = (float)stoi(lec);

	tex.texels = vector<Color>(tex.width * tex.height);
	for (int i = 0; i < tex.width * tex.height; i++)
	{
		lec = read_line_(in);
		r = stoi(lec) * tex.max / tex.c;

		lec = read_line_(in);
		g = stoi(lec) * tex.max / tex.c;

		lec = read_line_(in);
		b = stoi(lec) * tex.max / tex.c;

		tex.texels.at(i) = Color{ r, g, b };
	}
	in.close();
	return make_shared<Texture>(tex);
}