#include "resourcemanager.h"
#include "../application.h"
#include "SDL/SDL_image.h"
#include <app\debug\logging.h>

ResourceManager* ResourceManager::gInstance = NULL;

void ResourceManager::Clear()
{
	for (TextureResourceMap::iterator it = mTextures.begin(); it != mTextures.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
	}

	mTextures.clear();

	for (FontResourceMap::iterator it = mFonts.begin(); it != mFonts.end(); ++it)
	{
		TTF_CloseFont(it->second);
	}

	mFonts.clear();

	for (MixChunkMap::iterator it = mMixChunks.begin(); it != mMixChunks.end(); ++it)
	{
		Mix_FreeChunk(it->second);
	}

	mMixChunks.clear();

	for (MixMusicMap::iterator it = mMixMusics.begin(); it != mMixMusics.end(); ++it)
	{
		Mix_FreeMusic(it->second);
	}

	mMixMusics.clear();
}

SDL_Texture* ResourceManager::GetTexture(std::string filename)
{
	if (gApp->Options.UseDevDirectory)
	{
		filename = "../data/" + filename;
	}

	TextureResourceMap::iterator it = mTextures.find(filename);
	if (it != mTextures.end())
	{
		return it->second;
	}

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
	if (loadedSurface == NULL)
	{
		Debug::console("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gApp->Renderer(), loadedSurface);
		if (newTexture == NULL)
		{
			Debug::console("Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError());
		}
		else
		{
			mTextures[filename] = newTexture;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

TTF_Font* ResourceManager::GetFont(std::string filename, int size)
{
	if (gApp->Options.UseDevDirectory)
	{
		filename = "../data/" + filename;
	}

	FontResourceMap::iterator it = mFonts.find(filename);
	if (it != mFonts.end())
	{
		return it->second;
	}

	TTF_Font* font = TTF_OpenFont(filename.c_str(), size);
	if (font == NULL)
	{
		Debug::console("Failed to load font %s! Error: %s\n", filename.c_str(), TTF_GetError());
	}
	else
	{
		mFonts[filename] = font;
	}

	return font;
}


Mix_Chunk* ResourceManager::GetSFX(std::string filename)
{
	if (gApp->Options.UseDevDirectory)
	{
		filename = "../data/" + filename;
	}

	MixChunkMap::iterator it = mMixChunks.find(filename);
	if (it != mMixChunks.end())
	{
		return it->second;
	}

	Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
	if (sound == NULL)
	{
		Debug::console("Failed to load sound %s! Error: %s\n", filename.c_str(), Mix_GetError());
	}
	else
	{
		mMixChunks[filename] = sound;
	}

	return sound;
}

Mix_Music* ResourceManager::GetMusic(std::string filename)
{
	if (gApp->Options.UseDevDirectory)
	{
		filename = "../data/" + filename;
	}

	MixMusicMap::iterator it = mMixMusics.find(filename);
	if (it != mMixMusics.end())
	{
		return it->second;
	}

	Mix_Music* music = Mix_LoadMUS(filename.c_str());
	if (music == NULL)
	{
		Debug::console("Failed to load music %s! Error: %s\n", filename.c_str(), Mix_GetError());
	}
	else
	{
		mMixMusics[filename] = music;
	}

	return music;
}
