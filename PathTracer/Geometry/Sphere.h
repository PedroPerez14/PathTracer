/*
 * Author: Pedro José Pérez García
 * Date: 19/07/2021
 * Coms: Esferas con sus funciones y métodos
 */

#pragma once
#include "Shape.h"

class Sphere : public Shape
{
private:
	Vector3 center;
	Vector3 axis;
	Vector3 ref_point;
	float r;	//radius

public:
	Sphere(){}

	Sphere(Vector3 center, float r, shared_ptr<Material> mat)
	{
		this->center = center;
		this->r = r;
		this->mat = mat;
		axis = Vector3{ 0.0f, 2 * r, 0.0f };
		ref_point = Vector3{ center.x, center.y, center.z + r };
	}

	void uv(Vector3 p, float& u, float& v) override
	{
		Vector3 base_x = cross(center - ref_point, axis);
		Vector3 base_y = axis;
		Vector3 base_z = cross(base_x, axis);
		base_x.normalize();
		base_y.normalize();
		base_z.normalize();
		p = change_coord_system_point(p, base_x, base_y, base_z, center);
		Vector3 c{ 0, 0, 0 };
		u = atan2((p.x - c.x) / (p - c).mod(), (p.z - c.z) / (p - c).mod());
		v = acos((p.y - c.y) / (p - c).mod());
	}

	Vector3 intersect(const Vector3& o, const Vector3& d, bool& intersects) override
	{
		Vector3 intersection{ 0, 0, 0 };
		float a = d.mod() * d.mod();
		float b = 2 * dot(d, o - center);
		float c = (o - center).mod() * (o - center).mod() - r * r;
		float root = b * b - 4 * a * c;

		if (root >= 0.0f)
		{
			float t_small = (-b - sqrtf(root)) / (2 * a);
			float t_big = (-b + sqrtf(root)) / (2 * a);

			if (t_small >= 0.0f)
			{
				intersects = true;
				intersection = o + (d * t_small);
			}
			else if (t_big >= 0.0f)
			{
				intersects = true;
				intersection = o + (d * t_big);
			}
			else
			{
				intersects = false;
			}
		}
		else
		{
			intersects = false;
		}
		return intersection;
	}

	Vector3 normal_at_point(const Vector3& p) override
	{
		Vector3 retval = (p - center);
		retval.normalize();
		return retval;
	}

	Vector3 long_tan(const Vector3& surface_point) override
	{
		Vector3 retval = cross(axis, normal_at_point(surface_point));
		retval.normalize();
		return retval;
	}

	Vector3 lat_tan(const Vector3& surface_point) override
	{
		Vector3 retval = cross(normal_at_point(surface_point), long_tan(surface_point));
		retval.normalize();
		return retval;
	}

	void fresnel(Vector3 w_o, Vector3 n, Color& k_s, Color& k_t, const float& n_env, const bool& ray_through_air) override
	{
		w_o.normalize();
		n.normalize();
		float n1, n2;
		if (ray_through_air)
		{
			n1 = n_env;
			n2 = mat->n_fresnel;
		}
		else
		{
			n1 = mat->n_fresnel;
			n2 = n_env;
			n = n * -1.0f;
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_o * -1.0f, n);
		float sin_th_t_2 = mu * mu * (1.0f - (cos_th_entr * cos_th_entr));
		float cos_refrac = sqrtf(1.0f - sin_th_t_2);
		float p_paral = (n2 * cos_th_entr - n1 * cos_refrac) / (n2 * cos_th_entr + n1 * cos_refrac);
		float p_perp = (n1 * cos_th_entr - n2 * cos_refrac) / (n1 * cos_th_entr + n2 * cos_refrac);
		float fr = (p_paral * p_paral + p_perp * p_perp) / 2.0f;
		float ft = 1.0f - fr;
		k_s = Color{ fr, fr, fr };
		k_t = Color{ ft, ft, ft };
	}

	Vector3 refract_ray(Vector3 n, Vector3 w_entr, const float& n_env, bool& ray_through_air) override
	{
		n.normalize();
		w_entr.normalize();
		float n1, n2;
		if (ray_through_air)
		{
			n1 = n_env;
			n2 = mat->n_fresnel;
		}
		else
		{
			n1 = mat->n_fresnel;
			n2 = n_env;
			n = n * -1.0f;
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_entr * -1.0f, n);
		float sin_th_t_2 = mu * mu * (1.0f - (cos_th_entr * cos_th_entr));
		return w_entr * mu + n * (mu * cos_th_entr - sqrtf(1.0f - sin_th_t_2));
	}
};
