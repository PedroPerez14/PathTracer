/*
 * Author: Pedro José Pérez García
 * Date: 19/07/2021
 * Coms: Planos con sus funciones y métodos
 */

#pragma once
#include "Shape.h"

class Plane : protected Shape
{
private:
	float c;
	Vector3 n;
	Vector3 v1;
	Vector3 v2;
	Vector3 origin;
public:
	Plane(){}

	Plane(Vector3 origin, Vector3 v1, Vector3 v2, shared_ptr<Material> mat)
	{
		n = cross(v1, v2);
		n.normalize();
		c = dot(n, origin) * -1.0f;
		this->v1 = v1;
		this->v2 = v2;
		this->origin = origin;
		this->mat = mat;
	}

	void uv(Vector3 p, float& u, float& v) override
	{
		p = change_coord_system(p, v1, v2, dot(v1, v2), origin);
		u = p.x;
		v = p.y;
	}

	Vector3 intersect(const Vector3& o, const Vector3& d, bool& intersects) override
	{
		Vector3 intersection = Vector3{ 0, 0, 0 };
		float t = ((c + dot(o, n)) * -1.0f / dot(d, n));
		if (t <= (float)_EPSILON)
		{
			intersects = false;
		}
		else
		{
			intersects = true;
			intersection = Vector3{ o.x + t * d.x, o.y + t * d.y, o.z + t * d.z };
		}
		return intersection;
	}

	Vector3 normal_at_point(const Vector& p) override
	{
		return n;
	}

	Vector3 long_tan(const Vector3& surface_point) override
	{
		return v1;
	}

	Vector3 lat_tan(const Vector3& surface_point) override
	{
		return v2;
	}

	void fresnel(Vector3 w_o, Vector3 n, Color& k_s, Color& k_t, const float& n_env, const bool& ray_through_air) override
	{
		w_o.normalize();
		n.normalize();
		float n1 = n_env;
		float n2 = mat->n_fresnel;
		if (dot(w_o * -1.0f, n) > 0.0f)
		{
			n = n * -1.0f;
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_o * -1.0, n);
		float sin_th_t_2 = mu * mu * (1 - (cos_th_entr * cos_th_entr));
		float cos_refrac = sqrtf(1 - sin_th_t_2);
		float p_paral = (n2 * cos_th_entr - n1 * cos_refrac) / (n2 * cos_th_entr + n1 * cos_refrac);
		float p_perp = (n1 * cos_th_entr - n2 * cos_refrac) / (n1 * cos_th_entr + n2 * cos_refrac);
		float fr = (p_paral * p_paral + p_perp * p_perp) / 2.0f;
		float ft = 1 - fr;
		k_s = Color{ fr, fr, fr };
		k_t = Color{ ft, ft, ft };
	}

	Vector3 refract_ray(Vector3 n, Vector3 w_entr, const float& n_medio)
	{
		n.normalize();
		w_entr.normalize();
		float n1 = n_env;
		float n2 = mat->n_fresnel;
		if (dot(w_o * -1.0f, n) > 0.0f)
		{
			n = n * -1.0f;
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_entr * -1.0f, n);
		float sin_th_t_2 = mu * mu * (1 - (cos_th_entr * cos_th_entr));
		return w_entr * mu + n * (mu * cos_th_entr - sqrtf(1 - sin_th_t_2));
	}

};