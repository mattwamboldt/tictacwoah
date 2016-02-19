#ifndef SFMLIMAGEFILE_H
#define SFMLIMAGEFILE_H

#include <spriterengine/override/imagefile.h>
#include <SDL\SDL.h>
#include <string>

namespace SpriterEngine
{
	class SdlImageFile : public ImageFile
	{
	public:
		SdlImageFile(std::string initialFilePath, point initialDefaultPivot);
		void renderSprite(UniversalObjectInterface *spriteInfo) override;

	private:
		SDL_Texture* texture;
		void initializeFile();
	};

}

#endif // SFMLIMAGEFILE_H
