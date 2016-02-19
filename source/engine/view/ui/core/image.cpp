#include "image.h"
#include <app\application.h>
#include <app\resource\resourcemanager.h>

Image::Image() : ScreenObject()
{
	mColor.r = 255;
	mColor.g = 255;
	mColor.b = 255;
}

void Image::SetTexture(const char* path)
{
	mTexture = ResourceManager::Get()->GetTexture(path);
	if (mTexture)
	{
		mColor.r = 255;
		mColor.g = 255;
		mColor.b = 255;
		SDL_QueryTexture(mTexture, NULL, NULL, &(mBounds.w), &(mBounds.h));
	}
}

void Image::Render(int parentX, int parentY)
{
	if (!mTexture)
	{
		ScreenObject::Render(parentX, parentY);
	}
	else
	{
		// TODO: use color as a tint for the image
		SDL_Renderer* renderer = gApp->Renderer();
		SDL_Rect renderRect = mBounds;
		renderRect.x += parentX;
		renderRect.y += parentY;
		SDL_RenderCopy(renderer, mTexture, NULL, &renderRect);
	}
}