#ifndef SFMLSOUNDOBJECTINFOREFERENCE_H
#define SFMLSOUNDOBJECTINFOREFERENCE_H

#include <spriterengine/override/soundobjectinforeference.h>


namespace SpriterEngine
{
	class SdlSoundObjectInfoReference : public SoundObjectInfoReference
	{
	public:
		void playTrigger() override {}

	private:
		void setPlaybackVolume() override {}
		void setPlaybackPanning() override {}
	};
}

#endif // SFMLSOUNDOBJECTINFOREFERENCE_H
