/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: Clase con funciones virtuales para que la hereden las diferentes formas
 */

#pragma once

#include <iostream>
#include "../DataTypes/Vector3.h"
#include "../DataTypes/Material.h"


class Shape
{
protected:
	std::shared_ptr<Material> mat;
public:
	Shape(){}

	virtual Vector3 intersect(const Vector3& o, const Vector3& d, bool& intersects) = 0;

	virtual Vector3 normal_at_point(const Vector3& p) = 0;

	virtual Vector3 long_tan(const Vector3& surface_point) = 0;

	virtual Vector3 lat_tan(const Vector3& surface_point) = 0;

	virtual Vector3 fresnel(Vector3 w_o, Vector3 n, Color& k_s, Color& k_t, const float& n_env, const bool& ray_through_air) = 0;

	virtual Vector3 refract_ray(Vector3 n, const Vector3& w_entr, const float& n_env, bool& ray_through_air) = 0;

	virtual void uv(Vector3 p, float& azimuth, float& inclination)
	{
		std::cerr << "Error: not overridden!" << std::endl;
		azimuth = 0;
		inclination = 0;
	}

	Color get_color(const Vector3& p) // divido por 255?? nah, voy a tener todo entre 0 y 1 controlado
	{
		if (mat->has_texture)
		{
			float u, v;
			uv(p, u, v);
			return mat->tex->get_texel(u, v) * mat->mul;
		}
		//else
		return mat->k_d * mat->mul;
	}

	std::shared_ptr<Material> get_mat() const
	{
		return mat;
	}
};