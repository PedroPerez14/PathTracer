/*
 * Author: Pedro José Pérez García
 * Date: 19/07/2021
 * Coms: Cilindros con sus funciones y métodos
 */

#pragma once
#include "Shape.h"
#include "Plane.h"

class Cylinder : public Shape
{
private: 
	float r;
	float height;
	Vector3 axis;
	Vector3 origin;
	Vector3 dir1;
	Vector3 dir2;

public:
	Cylinder(){}

	//For infinite cylinders
	Cylinder(const Vector3& origin, const Vector3& axis, const float& r, shared_ptr<Material> mat)
	{
		this->axis = axis;
		this->origin = origin;
		this->r = r;
		this->height = 0;
		this->mat = mat;
		this->axis.normalize();

		this->dir1 = this->axis.perpendicular();
		this->dir2 = cross(this->axis, dir1);
		this->dir1.normalize();
		this->dir2.normalize();
	}

	//Finite cylinders, needs height data
	Cylinder(const Vector3& origin, const Vector3& axis, const float& r, const float& height, shared_ptr<Material> mat)
	{
		this->axis = axis;
		this->origin = origin;
		this->r = r;
		this->height = height;
		this->mat = mat;
		this->axis.normalize();

		this->dir1 = this->axis.perpendicular();
		this->dir2 = cross(this->axis, dir1);
		this->dir1.normalize();
		this->dir2.normalize();
	}

	void uv(Vector3 p, float& u, float& v) override
	{
		p = change_coord_system_point(p, dir1, dir2, axis, origin);
		Vector3 dist_origin = p - origin;
		u = atan2((p.x - origin.x) / dist_origin.mod(),
				  (p.z - origin.z) / dist_origin.mod());
		v = p.z;
	}

	Vector3 intersect(Vector3 o, Vector3 d, bool& intersects) override
	{
		Vector3 intersection{ 0, 0, 0 };
		Vector3 o2 = change_coord_system_point(o, dir1, dir2, axis);
		o2.z = 0;
		Vector3 d2 = change_coord_system_dir(d, dir1, dir2, axis);
		d2.z = 0;
		Vector3 origin2 = change_coord_system_point(origin, dir1, dir2, axis);
		origin2.z = 0;
		float a = d2.mod() * d2.mod();
		float b = 2 * dot(d2, o2 - origin2);
		float c = (o2 - origin2).mod() * (o2 - origin2).mod() - r * r;
		float root = b * b - 4 * a * c;

		if (root >= 0.0f)
		{
			float t_small = (-b - sqrt(root)) / (2 * a);
			float t_big = (-b + sqrt(root)) / (2 * a);

			if (t_small >= 0)
			{
				intersection = Vector3{o.x + t_small * d.x, o.y + t_small * d.y, o.z + t_small * d.z};
				intersects = true;
			}
			else if (t_big >= 0 )	//Camera inside the cylinder
			{
				intersection = Vector3{ o.x + t_big * d.x, o.y + t_big * d.y, o.z + t_big * d.z };
				intersects = true;
			}
			else
			{
				intersects = false;	//Cylinder is behind the camera
			}
		}
		else	//There is no solution for the equation -> does not intersect
		{
			intersects = false;
		}

		if (intersects && height != 0)
		{
			float u, v;
			uv(intersection, u, v);
			if (height >= v && v >= 0)
			{
				intersects = true;
			}
			else
			{
				intersects = false;
				bool intersects_2;
				Plane plane1 = Plane(origin + (axis * height), dir1, dir2, create_specular_material());
				Vector3 p2 = plane1.intersect(o, d, intersects_2);
				Vector3 dist = p2 - (origin + axis * height);
				intersects_2 = intersects_2 && dist.mod() <= r;
				bool intersects_3;
				Plane plane2 = Plane(origin, dir1, dir2, create_specular_material());
				Vector3 p3 = plane2.intersect(o, d, intersects_3);
				dist = p3 - origin;
				intersects_3 = intersects_3 && dist.mod() <= r;

				if (intersects_2 && !intersects_3)
				{
					intersects = true;
					intersection = p2;
				}
				else if (intersects_3 && !intersects_2)
				{
					intersects = true;
					intersection = p3;
				}
				else if (intersects_2 && intersects_3)
				{
					intersects = true;
					Vector3 dist_p2 = p2 - o;
					Vector3 dist_p3 = p3 - o;
					if (dist_p3.mod() > dist_p2.mod())
					{
						intersection = p2;
					}
					else
					{
						intersection = p3;
					}
				}
				else
				{
					intersects = false;
				}
			}
		}

		return intersection;
	}

	Vector3 normal_at_point(const Vector3& p) override
	{
		float u, v;
		uv(p, u, v);
		Vector3 retval;
		if (v >= height - (float)_EPSILON)
		{
			retval = axis;
		}
		else if (v <= (float)_EPSILON)
		{
			retval = axis * -1.0f;
		}
		else
		{
			retval = p - axis * v - origin;
			retval.normalize();
		}
		return retval;
	}

	Vector3 long_tan(const Vector3& surface_point) override
	{
		float u, v;
		uv(surface_point, u, v);
		if (v >= height - (float)_EPSILON || v <= (float)_EPSILON)
		{
			return dir1;
		}
		else
		{
			Vector3 retval = cross(axis, normal_at_point(surface_point));
			retval.normalize();
			return retval;
		}
	}

	Vector3 lat_tan(const Vector3& surface_point) override
	{
		float u, v;
		uv(surface_point, u, v);
		if (v >= height - (float)_EPSILON || v <= (float)_EPSILON)
		{
			return dir2;
		}
		else
		{
			return axis;
		}
	}

	void fresnel(Vector3 w_o, Vector3 n, Color& k_s, Color& k_t, 
									const float& n_env, const bool& ray_on_air) override
	{
		w_o.normalize();
		n.normalize();
		float n1, n2;
		if (ray_on_air)
		{
			n1 = n_env;
			n2 = mat->n_fresnel;
		}
		else				//Sigo sin fiarme de la chapuza que hice para fresnel pero funciona
		{
			n1 = mat->n_fresnel;
			n2 = n_env;
			n = n * -1.0f;
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_o * -1.0f, n);
		float sin_th_t_2 = mu * mu * (1 - (cos_th_entr * cos_th_entr));
		float cos_refrac = sqrtf(1 - sin_th_t_2);
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
		}
		float mu = n1 / n2;
		float cos_th_entr = dot(w_entr * -1.0f, n);
		float sin_th_t_2 = mu * mu * (1 - (cos_th_entr * cos_th_entr));
		ray_through_air = !ray_through_air;
		return w_entr * mu + n * (mu * cos_th_entr - sqrtf(1 - sin_th_t_2));
	}
};
