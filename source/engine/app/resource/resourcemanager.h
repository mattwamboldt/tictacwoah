/*
Copied from Experiments project to test the build process. Needs to be reworked to
an improved version of the hawkeye loader that is more robust
*/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_Mixer.h"
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, SDL_Texture*> TextureResourceMap;
typedef std::unordered_map<std::string, TTF_Font*> FontResourceMap;
typedef std::unordered_map<std::string, Mix_Chunk*> MixChunkMap;

// This version of a resource manager will load a set of specific file types
// And keeps a map from file name to loaded data to look up. The memory/resources
// need to be manually freed to keep things simple
class ResourceManager
{
public:
	static void Create() { if (!gInstance) gInstance = new ResourceManager(); }
	static ResourceManager* Get(){ return gInstance; }
	static void Destroy() { if (gInstance) delete gInstance; }

	~ResourceManager(){ Clear(); }
	void Clear();

	SDL_Texture* GetTexture(std::string filename);
	TTF_Font* GetFont(std::string filename, int size);
	Mix_Chunk* GetSFX(std::string filename);

private:
	TextureResourceMap mTextures;
	FontResourceMap mFonts;
	MixChunkMap mMixChunks;

	//Making it a singleton for now
	static ResourceManager* gInstance;
};

#endif