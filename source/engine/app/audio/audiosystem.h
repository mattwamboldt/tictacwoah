#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

// This is the start of an interface for an audio ayatem, this system will use SDL Mixer.
class AudioSystem
{
public:
	bool Init();
	bool PlaySound(const char* name);
	void Destroy();
};

#endif