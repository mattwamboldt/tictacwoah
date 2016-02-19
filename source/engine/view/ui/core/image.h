#ifndef SCREEN_IMAGE_H
#define SCREEN_IMAGE_H

#include "screenobject.h"

class Image : public ScreenObject
{
public:
	Image();
	Image(const char* path){ SetTexture(path); }
	void SetTexture(const char* path);
	virtual void Render(int parentX = 0, int parentY = 0);
private:
	SDL_Texture* mTexture;
};

#endif