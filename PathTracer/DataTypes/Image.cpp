/*
 * Author: Pedro José Pérez García
 * Date: 22/07/2021
 * Coms: Separar implementaciones y definiciones que causen problemas
 */

#pragma once
#include "Image.h"

string read_line(ifstream& in)
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