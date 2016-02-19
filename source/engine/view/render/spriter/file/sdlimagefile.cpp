#include "sdlimagefile.h"
#include <spriterengine/global/settings.h>
#include <spriterengine/objectinfo/universalobjectinterface.h>
#include <app\application.h>
#include <app\resource\resourcemanager.h>
#include <app\debug\logging.h>

namespace SpriterEngine
{
	SdlImageFile::SdlImageFile(std::string initialFilePath, point initialDefaultPivot) :
		ImageFile(initialFilePath,initialDefaultPivot)
	{
		initializeFile();
	}

	void SdlImageFile::initializeFile()
	{
		texture = ResourceManager::Get()->GetTexture(path());
		if (texture == NULL)
		{
			Settings::error("initializeFile - sfml texture unable to load file from path");
		}
	}

	void SdlImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		if (texture)
		{
			int w, h;
			SDL_QueryTexture(texture, NULL, NULL, &w, &h);
			SDL_Point center = { spriteInfo->getPivot().x * w *spriteInfo->getScale().x, spriteInfo->getPivot().y * h * spriteInfo->getScale().y };
			SDL_Rect renderRect = {
				spriteInfo->getPosition().x - center.x,
				spriteInfo->getPosition().y - center.y,
				w *spriteInfo->getScale().x,
				h * spriteInfo->getScale().y
			};

			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture, 255 * spriteInfo->getAlpha());
			SDL_RenderCopyEx(gApp->Renderer(), texture, NULL, &renderRect, toDegrees(spriteInfo->getAngle()), &center, SDL_FLIP_NONE);
		}
	}
}
