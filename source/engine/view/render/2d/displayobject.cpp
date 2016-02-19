#include "displayobject.h"
#include <SDL\SDL.h>
#include <app\application.h>

void DisplayObject::Render()
{
	// By default a display object renders as a white rectangle
	if (visible)
	{
		SDL_Rect fillRect = { x, y, width, height };
		SDL_SetRenderDrawColor(gApp->Renderer(), color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(gApp->Renderer(), &fillRect);
	}
}
