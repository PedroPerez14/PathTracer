/*
 * Author: Pedro José Pérez García
 * Date: 19/07/2021
 * Coms: Planos FINITOS cuadrados (quads de cuadriláteros) con sus funciones y métodos
 */

#pragma once
#include "Shape.h"

class Quad : public Shape
{
private:
	float c;
	Vector3 n;
	Vector3 v1;
	Vector3 v2;
	Vector3 origin;
public:
	Quad(){}

	Quad(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, shared_ptr<Material> mat)
	{
		origin = p0;	//origin is located in one corner, not in the center of the quad
		v1 = p1 - p0;
		v2 = p2 - p0;
		Vector3 aux = p2 + v1;
		if (p3 != aux)
		{
			cerr << "ERROR: Incorrect quad dimensions! Errors might happen during execution" << endl;
		}
		this->mat = mat;
		n = cross(v1, v2);
		n.normalize();
		c = -dot(n, origin);
		//TODO delete
		cout << n.to_string() << endl;
		cout << c << endl;
		cout << v1.to_string() << endl;
		cout << v2.to_string() << endl;
		cout << "--------------------------" << endl;
	}

	Quad(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, shared_ptr<Material> mat, bool inv_normal)
	{
		origin = p0;	//origin is located in one corner, not in the center of the quad
		v1 = p1 - p0;
		v2 = p2 - p0;
		Vector3 aux = p2 + v1;
		if (p3 != aux)
		{
			cerr << "ERROR: Incorrect quad dimensions! Errors might happen during execution" << endl;
		}
		this->mat = mat;
		n = cross(v1, v2);
		n.normalize();
		if (inv_normal)
		{
			n = n * -1.0f;
		}
		c = -dot(n, origin);
		//TODO delete
		cout << n.to_string() << endl;
		cout << c << endl;
		cout << v1.to_string() << endl;
		cout << v2.to_string() << endl;
		cout << "--------------------------" << endl;
	}

	void uv(Vector3 p, float& u, float& v) override
	{
		p = change_coord_system_point(p, v1, v2, cross(v1, v2), origin); //TODO normalize???
		u = p.x;
		v = p.y;
	}

	Vector3 intersect(Vector3 o, Vector3 d, bool& intersects) override
	{
		Vector3 intersection{ 0, 0, 0 };
		float t = (-1.0f * (c + dot(o, n)) / dot(d, n));
		if (t <= 0.0f)
		{
			intersects = false;
			intersection = Vector3{0.0f, 0.0f, 0.0f};
		}
		else
		{
			intersection = Vector3{ o.x + d.x * t, o.y + d.y * t, o.z + d.z * t };
			float u, v;
			uv(intersection, u, v);
			intersects = (u < 1 && u > 0 && v < 1 && v > 0);
		}
		return intersection;
	}

	Vector3 normal_at_point(const Vector3& p) override
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

	Vector3 refract_ray(Vector3 n, Vector3 w_entr, const float& n_medio, bool& ray_through_air) override
	{
		n.normalize();
		w_entr.normalize();
		float n1 = n_medio;
		float n2 = mat->n_fresnel;
		if (dot(w_entr * -1.0f, n) > 0.0f)
		{
			n = n * -1.0f;
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_entr * -1.0f, n);
		float sin_th_t_2 = mu * mu * (1 - (cos_th_entr * cos_th_entr));
		return w_entr * mu + n * (mu * cos_th_entr - sqrtf(1 - sin_th_t_2));
	}
	
};
