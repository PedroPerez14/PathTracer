/*
 * Author: Pedro José Pérez García
 * Date: 22/07/2021
 * Coms: Tengo que separar declaraciones e implementaciones
 */
#pragma once
#include "Vector3.h"

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
    float max = (color.r < color.g) ? color.g : color.r;
    return ((max < color.b) ? color.b : max);
    //return std::max(std::max(color.r, color.g), color.b);
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

