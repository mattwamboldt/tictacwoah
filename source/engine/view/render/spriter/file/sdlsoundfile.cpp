#include "sdlsoundfile.h"

#include <spriterengine/global/settings.h>

#include "..\object\sdlsoundobjectinforeference.h"

namespace SpriterEngine
{
	SdlSoundFile::SdlSoundFile(std::string initialFilePath) :
		SoundFile(initialFilePath)
	{
		initializeFile();
	}

	void SdlSoundFile::initializeFile()
	{
		Settings::error("SdlSoundFile::initializeFile - Cannot load sound files yet. \"" + path() + "\"");
	}

	SoundObjectInfoReference * SdlSoundFile::newSoundInfoReference()
	{
		return new SdlSoundObjectInfoReference();
	}

}
