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
		return sqrtf(x * x + y * y + z * z);
	}

	void normalize()
	{
		float modulus = this->mod();
		x /= modulus;
		y /= modulus;
		z /= modulus;
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
		return Vector3{ x * scalar, y * scalar, z * scalar };
	}

    Vector3 operator/(const float& scalar) const
    {
        return Vector3{ x / scalar, y / scalar, z / scalar };
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

float dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3{ v1.y * v2.z - v1.z * v2.y, -(v1.x * v2.z - v1.z * v2.x), v1.x * v2.y - v1.y * v2.x };
}

float angle(const Vector3& v1, const Vector3& v2)
{
	float cos = dot(v1, v2) / v1.mod() / v2.mod();
	return acos(cos);
}

float max_px(const Color& color)
{
    return std::max(std::max(color.r, color.g), color.b);
}

// Color space transition functions //

Color RGBtoXYZ(const Color& px)
{
    float r, g, b, x, y, z;
    r = px.r;
    g = px.g;
    b = px.b;
    Color retval{};
    if (r > 0.4045)
    {
        r = pow((r + 0.055) / 1.055, 2.4);
    }
    else
    {
        r = r / 12.92;
    }

    if (g > 0.4045)
    {
        g = pow((g + 0.055) / 1.055, 2.4);
    }
    else
    {
        g = g / 12.92;
    }

    if (b > 0.4045)
    {
        b = pow((b + 0.055) / 1.055, 2.4);
    }
    else
    {
        b = b / 12.92;
    }
    r *= 100;
    g *= 100;
    b *= 100;

    x = r * 0.4124 + g * 0.3576 + b * 0.1805;
    y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    z = r * 0.0193 + g * 0.1192 + b * 0.9505;
    retval = Color{ x, y, z };
    return retval;
}

Color XYZtoLAB(const Color& p)
{
    float l, a, b, x, y, z;
    x = p.r / 95.047;
    y = p.g / 100.0;
    z = p.b / 108.883;

    x = (x > 0.008856) ? cbrt(x) : (7.787 * x + 16.0 / 116.0);
    y = (y > 0.008856) ? cbrt(y) : (7.787 * y + 16.0 / 116.0);
    z = (z > 0.008856) ? cbrt(z) : (7.787 * z + 16.0 / 116.0);

    l = (116.0 * y) - 16;
    a = 500 * (x - y);
    b = 200 * (y - z);
    return Color{ l, a, b };
}

Color LABtoXYZ(const Color& p)
{
    float x, y, z;

    y = (p.r + 16.0) / 116.0;
    x = p.g / 500.0 + y;
    z = y - p.b / 200.0;

    if (pow(y, 3.0) > 0.008856)
    {
        y = pow(y, 3.0);
    }
    else
    {
        y = (y - 16.0 / 116.0) / 7.787;
    }
    if (pow(x, 3.0) > 0.008856)
    {
        x = pow(x, 3.0);
    }
    else
    {
        x = (x - 16.0 / 116.0) / 7.787;
    }
    if (pow(z, 3.0) > 0.008856)
    {
        z = pow(z, 3.0);
    }
    else
    {
        z = (z - 16.0 / 116.0) / 7.787;
    }

    x = x * 95.047;
    y = y * 100.0;
    z = z * 108.883;
    return Color{ x, y, z };
}

Color XYZtoRGB(const Color& p)
{
    float x, y, z, r, g, b;
    x = p.r / 100.0;
    y = p.g / 100.0;
    z = p.b / 100.0;

    r = x * 3.2406 + y * -1.5372 + z * -0.4986;
    g = x * -0.9689 + y * 1.8758 + z * 0.0415;
    b = x * 0.0557 + y * -0.2040 + z * 1.0570;

    if (r > 0.0031308)
    {
        r = 1.055 * (pow(r, (1.0 / 2.4))) - 0.055;
    }
    else
    {
        r = 12.92 * r;
    }
    if (g > 0.0031308)
    {
        g = 1.055 * (pow(g, (1.0 / 2.4))) - 0.055;
    }
    else
    {
        g = 12.92 * g;
    }
    if (b > 0.0031308)
    {
        b = 1.055 * (pow(b, (1.0 / 2.4))) - 0.055;
    }
    else
    {
        b = 12.92 * b;
    }

    return Color{ r, g, b };
}

Color XYZtoYxy(const Color& p)
{
    float X, Y, Z;
    X = p.r;
    Y = p.g;
    Z = p.b;
    return Color{ Y, X / (X + Y + Z), Y / (X + Y + Z) };
}

Color YxytoXYZ(const Color& p)
{
    float Y, x, y;
    Y = p.r;
    x = p.g;
    y = p.b;
    return Color{ x * (Y / y), Y, (1 - x - y) * (Y / y) };
}
