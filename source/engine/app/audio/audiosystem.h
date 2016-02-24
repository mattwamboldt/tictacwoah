#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <SDL\SDL_mixer.h>

// This is the start of an interface for an audio ayatem, this system will use SDL Mixer.
class AudioSystem
{
public:
	bool Init();
	bool PlaySound(const char* name);
	bool PlayMusic(const char* name);
	void Destroy();

private:
	Mix_Music* mMusic;
};

#endif