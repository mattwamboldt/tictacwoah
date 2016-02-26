#include "screenline.h"
#include <app\application.h>

ScreenLine::ScreenLine(const Line& line, Point tileSize)
{
	mTileSize = tileSize;
	Change(line);
}

void ScreenLine::Change(const Line& line)
{
	mBounds.x = line.start.x * mTileSize.x + mTileSize.x / 2;
	mBounds.y = line.start.y * mTileSize.y + mTileSize.y / 2;

	int scaledLength = (line.length - 1) * mTileSize.x;
	
	if (line.direction == HORIZONTAL)
	{
		mBounds.w = scaledLength;
		mBounds.h = 0;

	}
	else if (line.direction == VERTICAL)
	{
		mBounds.w = 0;
		mBounds.h = scaledLength;
	}
	else if (line.direction == DOWN_LEFT)
	{
		mBounds.w = -scaledLength;
		mBounds.h = scaledLength;
	}
	else if (line.direction == DOWN_RIGHT)
	{
		mBounds.w = scaledLength;
		mBounds.h = scaledLength;
	}

	mColor = Color(0xFFFFFFFF);
}

void ScreenLine::Render(int parentX, int parentY)
{
	SDL_Renderer* screen = gApp->Renderer();
	SDL_SetRenderDrawColor(screen, mColor.r, mColor.g, mColor.b, 255);

	SDL_RenderDrawLine(
		screen,
		parentX + mBounds.x,
		parentY + mBounds.y,
		parentX + mBounds.x + mBounds.w,
		parentY + mBounds.y + mBounds.h
	);
}
