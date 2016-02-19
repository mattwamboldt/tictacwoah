#include "sdlboxinstanceinfo.h"

#include <spriterengine/global/settings.h>
#include <app\application.h>

namespace SpriterEngine
{

	SdlBoxInstanceInfo::SdlBoxInstanceInfo(point initialSize) :
		BoxInstanceInfo(initialSize)
	{
		rectangle.w = initialSize.x;
		rectangle.h = initialSize.y;
	}

	void SdlBoxInstanceInfo::render()
	{
		if (Settings::renderDebugBoxes)
		{
			// TODO: Need to figure out how to render a rotated rect in the best way possible, maybe a prerendered texture that's scaled, i dunno
			// For now draw a basic rectangle in the right place and sizes at least
			SDL_Rect renderRect = { getPosition().x, getPosition().y, rectangle.x * getScale().x, rectangle.y * getScale().y };
			SDL_SetRenderDrawColor(gApp->Renderer(), 255, 255, 255, 255);
			SDL_RenderFillRect(gApp->Renderer(), &renderRect);
		}
	}

}
