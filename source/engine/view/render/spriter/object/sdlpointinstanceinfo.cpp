#include "sdlpointinstanceinfo.h"

#include <spriterengine/global/settings.h>
#include <app\application.h>
#include <SDL\SDL.h>

namespace SpriterEngine
{
	SdlPointInstanceInfo::SdlPointInstanceInfo() :
		size(10) { }

	void SdlPointInstanceInfo::render()
	{
		if (Settings::renderDebugPoints)
		{
			SDL_Rect rect = { getPosition().x - 5, getPosition().y - 5, 10, 10 };
			SDL_SetRenderDrawColor(gApp->Renderer(), 255, 0, 0, 255);
			SDL_RenderFillRect(gApp->Renderer(), &rect);
		}
	}
}
