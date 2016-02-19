#ifndef SFMLSOUNDFILE_H
#define SFMLSOUNDFILE_H

#include <spriterengine/override/soundfile.h>

// TODO: Support sound files in the engine at some point

namespace SpriterEngine
{
	class SdlSoundFile : public SoundFile
	{
	public:
		SdlSoundFile(std::string initialFilePath);

		SoundObjectInfoReference * newSoundInfoReference();

	private:
		void initializeFile();
	};
}

#endif // SFMLSOUNDFILE_H
