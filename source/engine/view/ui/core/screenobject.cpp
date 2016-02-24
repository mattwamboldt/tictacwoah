#include "screenobject.h"
#include <app\application.h>
#include <random>

ScreenObject::ScreenObject()
{
	// By default a screen object is a 100 x 100 box wuth a random color for debugging z-order
	mBounds = { 0, 0, 100, 100 };
	mVisible = true;
	mEnabled = true;
	mColor.a = 255;
	mColor.r = rand() % 255;
	mColor.g = rand() % 255;
	mColor.b = rand() % 255;
	mHasFocus = false;
	mFocusOrder = -1;
}

// ---------------
// RENDERING
// ---------------

// If an object is on the screen it's needs to be shown to the viewer
// To handle hierarchy we'll evetually want a screen matrix stack, or something
// along those lines, but for basic layout this'll do
void ScreenObject::Render(int parentX, int parentY)
{
	SDL_Renderer* renderer = gApp->Renderer();
	SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
	SDL_Rect renderRect = mBounds;
	renderRect.x += parentX;
	renderRect.y += parentY;
	SDL_RenderFillRect(renderer, &renderRect);
}

// If we're rendering we need to be able to set the objects visibility
bool ScreenObject::Visible()
{
	return mVisible;
}

void ScreenObject::Visible(bool visible)
{
	mVisible = visible;
}

// Control where the object is relative to it's parent
void ScreenObject::X(int x)
{
	mBounds.x = x;
}

int ScreenObject::X()
{
	return mBounds.x;
}

void ScreenObject::Y(int y)
{
	mBounds.y = y;
}

int ScreenObject::Y()
{
	return mBounds.y;
}

void ScreenObject::Position(int x, int y)
{
	mBounds.x = x;
	mBounds.y = y;
}

Point ScreenObject::Position()
{
	return Point(mBounds.x, mBounds.y);
}

// Control how big it is 
void ScreenObject::Width(int width)
{
	mBounds.w = width;
}

int ScreenObject::Width()
{
	return mBounds.w;
}

void ScreenObject::Height(int height)
{
	mBounds.h = height;
}

int ScreenObject::Height()
{
	return mBounds.h;
}

void ScreenObject::Dimensions(int width, int height)
{
	mBounds.w = width;
	mBounds.h = height;
}

Point ScreenObject::Dimensions()
{
	return Point(mBounds.w, mBounds.h);
}

// What Color it is
void ScreenObject::SetColor(Color color)
{
	mColor = color;
}

Color ScreenObject::GetColor()
{
	return mColor;
}

bool ScreenObject::Enabled()
{
	return mEnabled;
}

void ScreenObject::Enabled(bool enabled)
{
	mEnabled = enabled;
}

void ScreenObject::Update()
{
	if (mAnimating)
	{
		Uint32 currentTicks = SDL_GetTicks() - mStartTicks;
		
		if (currentTicks >= mEndTicks)
		{
			mBounds.x = mDestLocation.x;
			mBounds.y = mDestLocation.y;
			mAnimating = false;
			if (mAnimHandler) mAnimHandler();
		}
		else
		{
			float t = (float)currentTicks / (float)mEndTicks;
			mBounds.x = (int)(mStartLocation.x + (mDestLocation.x - mStartLocation.x) * t);
			mBounds.y = (int)(mStartLocation.y + (mDestLocation.y - mStartLocation.y) * t);
		}
	}
}

void ScreenObject::Move(int x, int y, Uint32 ms)
{
	mStartTicks = SDL_GetTicks();
	mEndTicks = ms;
	mStartLocation.x = mBounds.x;
	mStartLocation.y = mBounds.y;
	mDestLocation.x = x;
	mDestLocation.y = y;
	mAnimating = true;
	mAnimHandler.clear();
}

void ScreenObject::Move(int x, int y, Uint32 ms, AnimationCompleteHandler onComplete)
{
	Move(x, y, ms);
	mAnimHandler = onComplete;
}
