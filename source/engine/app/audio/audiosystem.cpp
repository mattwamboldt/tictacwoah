#include "audiosystem.h"
#include "SDL/SDL_mixer.h"
#include <app\debug\logging.h>
#include <app\resource\resourcemanager.h>

bool AudioSystem::Init()
{
	mMusic = NULL;

	int initFlags = Mix_Init(MIX_INIT_OGG);
	if ((initFlags & MIX_INIT_OGG) != MIX_INIT_OGG)
	{
		Debug::console("Mix_Init: Failed to init required ogg support!\n");
		Debug::console("Mix_Init: %s\n", Mix_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		Debug::console("Mix_OpenAudio: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

bool AudioSystem::PlaySound(const char* name)
{
	Mix_Chunk* sound = ResourceManager::Get()->GetSFX(name);
	if (sound && Mix_PlayChannel(-1, sound, 0) != -1)
	{
		return true;
	}

	return false;
}


bool AudioSystem::PlayMusic(const char* name)
{
	//TODO: Mis fade ends up pausing the game waiting for the audio to fade out before fading in the next track.
	if (mMusic)
	{
		Mix_FadeOutMusic(200);
	}

	mMusic = ResourceManager::Get()->GetMusic(name);
	if (mMusic && Mix_FadeInMusic(mMusic, -1, 200) != -1)
	{
		return true;
	}

	return false;
}

void AudioSystem::Destroy()
{
	Mix_CloseAudio();
	Mix_Quit();
}
