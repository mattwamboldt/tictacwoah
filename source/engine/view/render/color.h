#ifndef RENDERING_COLOR_H
#define RENDERING_COLOR_H

#include <SDL/SDL.h>

struct Color
{
    Color()
    {
        r = 0;
        g = 0;
        b = 0;
        a = 255;
    }

    Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a = 255)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    Color(Uint32 argb)
    {
        r = (argb >> 16) & 255;
        g = (argb >> 8) & 255;
        b = argb & 255;
        a = (argb >> 24) & 255;
    }

    void operator*=(float value)
    {
		r = (Uint8)(r * value);
		g = (Uint8)(g * value);
		b = (Uint8)(b * value);
    }

	operator SDL_Color()
	{
		return { r, g, b, a };
	}

    friend Color operator*(const Color& c, float value)
    {
		return Color((Uint8)(c.r * value), (Uint8)(c.g * value), (Uint8)(c.b * value));
    }

    friend bool operator==(const Color& c1, const Color& c2)
    {
        return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
    }

	friend bool operator!=(const Color& c1, const Color& c2)
	{
		return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b || c1.a != c2.a;
	}

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

#endif