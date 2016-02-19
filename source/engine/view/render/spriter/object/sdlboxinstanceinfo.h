#ifndef SFMLBOXINSTANCEINFO_H
#define SFMLBOXINSTANCEINFO_H

#include <SDL/SDL.h>
#include <spriterengine/objectinfo/boxinstanceinfo.h>

namespace SpriterEngine
{

	class SdlBoxInstanceInfo : public BoxInstanceInfo
	{
	public:
		SdlBoxInstanceInfo(point initialSize);

		void render() override;

	private:
		SDL_Rect rectangle;
	};
}

#endif // SFMLBOXINSTANCEINFO_H
