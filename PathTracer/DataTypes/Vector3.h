/*
 * Author: Pedro José Pérez García
 * Date: 16/07/2021
 * Coms: x y z , r g b , ahora son lo mismo
 */

#pragma once
#include <string>
#include <algorithm>

typedef struct Vector3
{
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };

	float mod() const 
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	void normalize()
	{
		float modulus = this->mod();
		this->x = this->x / modulus;
		this->y = this->y / modulus;
		this->z = this->z / modulus;
	}

	std::string to_string() const
	{
		return "[ " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "]";
	}

	Vector3 operator-(Vector3 v) const 
	{
		return Vector3{x - v.x, y - v.y, z - v.z};
	}

	Vector3 operator+(Vector3 v) const
	{
		return Vector3{ x + v.x, y + v.y, z + v.z };
	}

	Vector3 operator*(const float& scalar) const
	{
		return Vector3{ this->x * scalar, this->y * scalar, this->z * scalar };
	}

    Vector3 operator/(const float& scalar) const
    {
        return Vector3{ this->x / scalar, this->y / scalar, this->z / scalar };
    }

	bool operator==(const Vector3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}
	
	bool operator!=(const Vector3& v) const
	{
		return (x != v.x || y != v.y || z != v.z);
	}

	Vector3 perpendicular() const	//Returns a perpendicular vector to the one given
	{
		if (x == 0)
		{
			return Vector3{ 0, -z, y };
		}
		else
		{
			return Vector3{ -y, x, 0 };
		}
	}

	void clamp(float max = 1.0) {
		if (r > max) { r = max; }
		if (g > max) { g = max; }
		if (b > max) { b = max; }
		if (r < 0.0f) { r = 0.0f; }
		if (g < 0.0f) { g = 0.0f; }
		if (b < 0.0f) { b = 0.0f; }
	}

	void equalize(float eq = 1.0)
	{
		r = r / eq;
		g = g / eq;
		b = b / eq;
	}

	void equalize_and_clamp(float V)
	{
		r = (r > V) ? 1.0f : (r / V);
		g = (g > V) ? 1.0f : (g / V);
		b = (b > V) ? 1.0f : (b / V);
	}

	void gamma_curve(float eq, float gamma)
	{
		equalize(eq);
		r = powf(r, (1.0f / gamma));
		g = powf(g, (1.0f / gamma));
		b = powf(b, (1.0f / gamma));
	}

	void clamp_and_gamma_curve(float V, float gamma)
	{
		equalize_and_clamp(V);
		r = powf(r, (1.0f / gamma));
		g = powf(g, (1.0f / gamma));
		b = powf(b, (1.0f / gamma));
	}

	void reinhard_global(const float& r_avg, const float& g_avg, const float& b_avg, const float img_MAX, const float a) {
		// Erik Reinhard, 2002
		float r_scaled, g_scaled, b_scaled;
		r_scaled = r * (a / r_avg);
		g_scaled = g * (a / g_avg);
		b_scaled = b * (a / b_avg);
		r = (r_scaled * (1 + (r_scaled / (img_MAX * img_MAX)))) / (1 + r_scaled);
		g = (g_scaled * (1 + (g_scaled / (img_MAX * img_MAX)))) / (1 + g_scaled);
		b = (b_scaled * (1 + (b_scaled / (img_MAX * img_MAX)))) / (1 + b_scaled);
	}

	void reinhard_global(const float& l_avg, const float& img_MAX, const float a) {
		// Erik Reinhard, 2002
		float l_scaled = (float)(r * (float)(a / l_avg));
		this->r = (float)((float)l_scaled * (float)(1.0f + (float)(l_scaled / (float)(img_MAX * img_MAX)))) / (float)(1.0f + l_scaled);
	}

    Vector3 operator*(const Vector3& color) const
    {
        return Vector3{ r * color.r, g * color.g, b * color.b};
    }

}Vector3;
typedef Vector3 Color;

float dot(const Vector3& v1, const Vector3& v2);

Vector3 cross(const Vector3& v1, const Vector3& v2);

float angle(const Vector3& v1, const Vector3& v2);

float max_px(const Color& color);

// Color space transition functions //

Color RGBtoXYZ(const Color& px);

Color XYZtoLAB(const Color& p);

Color LABtoXYZ(const Color& p);

Color XYZtoRGB(const Color& p);

Color XYZtoYxy(const Color& p);

Color YxytoXYZ(const Color& p);
