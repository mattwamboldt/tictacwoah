#include "text.h"
#include <app\resource\resourcemanager.h>
#include <app\application.h>
#include <app\debug\logging.h>

Text::Text(std::string text, std::string font, int fontSize)
{
	mContent = text;
	mFontName = font;
	mFontSize = fontSize;
	mFont = ResourceManager::Get()->GetFont(font, fontSize);
	Debug::console("font %s, max height %d, faces %d\n", font.c_str(), TTF_FontHeight(mFont), TTF_FontFaces(mFont));
	mWrapEnabled = false;
	mHorizontalAlignment = LEFT;
	mVerticalAlignment = CENTER;
	mRenderedResult = NULL;
	mRequiresRedraw = true;
	mShowOverflow = true;
	mScrollPosition = { 0, 0 };
	mRenderedBounds = { 0, 0, 0, 0 };
	mColor = Color(0xFF000000);
}

Text::~Text()
{
	if (mRenderedResult)
	{
		SDL_DestroyTexture(mRenderedResult);
		mRenderedResult = NULL;
	}
}

void Text::Render(int parentX, int parentY)
{
	if (mRequiresRedraw)
	{
		Draw();
	}

	if (mRenderedResult)
	{
		SDL_Rect renderRect = mBounds;
		SDL_Rect sourceRect = mRenderedBounds;

		// Horizontal position
		if (sourceRect.w <= renderRect.w || mShowOverflow)
		{
			renderRect.w = sourceRect.w;
			if (mHorizontalAlignment == CENTER)
			{
				renderRect.x += (mBounds.w - mRenderedBounds.w) / 2;
			}
			else if (mHorizontalAlignment == RIGHT)
			{
				renderRect.x += mBounds.w - mRenderedBounds.w;
			}
		}
		else
		{
			sourceRect.w = renderRect.w;
			sourceRect.x = mScrollPosition.x;
		}

		// Vertical Position
		if (sourceRect.h <= renderRect.h || mShowOverflow)
		{
			renderRect.h = sourceRect.h;
			if (mVerticalAlignment == CENTER)
			{
				renderRect.y += (mBounds.h - mRenderedBounds.h) / 2;
			}
			else if (mVerticalAlignment == BOTTOM)
			{
				renderRect.y += mBounds.h - mRenderedBounds.h;
			}
		}
		else
		{
			sourceRect.h = renderRect.h;
			sourceRect.y = mScrollPosition.y;
		}

		renderRect.x += parentX;
		renderRect.y += parentY;

		SDL_RenderCopy(gApp->Renderer(), mRenderedResult, &sourceRect, &renderRect);
	}
}

void Text::Width(int width)
{
	mBounds.w = width;
	SetRedraw(mWrapEnabled);
}

void Text::Dimensions(int width, int height)
{
	mBounds.w = width;
	mBounds.h = height;
	SetRedraw(mWrapEnabled);
}

void Text::SetText(std::string text)
{
	SetRedraw(mContent != text);
	mContent = text;
}

void Text::SetFont(std::string font, int size)
{
	if (font != mFontName || size != mFontSize)
	{
		mFontName = font;
		mFontSize = size;
		mFont = ResourceManager::Get()->GetFont(font, size);
		SetRedraw();
	}
}

void Text::HorizontalAlign(Align alignment)
{
	if (alignment != mHorizontalAlignment)
	{
		mHorizontalAlignment = alignment;
		// TODO: in the future this will require a redraw for multiline text
	}
}

void Text::VerticalAlign(Align alignment)
{
	if (alignment != mVerticalAlignment)
	{
		mVerticalAlignment = alignment;
	}
}

void Text::SetWrap(bool enabled)
{
	if (enabled != mWrapEnabled)
	{
		mWrapEnabled = enabled;
		SetRedraw();
	}
}

int Text::LineHeight()
{
	return TTF_FontHeight(mFont);
}

void Text::Draw()
{
	if (mRenderedResult)
	{
		SDL_DestroyTexture(mRenderedResult);
		mRenderedResult = NULL;
	}

	if (mFont)
	{
		//Render text surface
		SDL_Surface* textSurface = NULL;

		if (mWrapEnabled)
		{
			textSurface = TTF_RenderUTF8_Blended_Wrapped(mFont, mContent.c_str(), mColor, mBounds.w);
		}
		else
		{
			textSurface = TTF_RenderUTF8_Blended(mFont, mContent.c_str(), mColor);
		}

		if (textSurface == NULL)
		{
			Debug::console("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			mRenderedResult = SDL_CreateTextureFromSurface(gApp->Renderer(), textSurface);
			if (mRenderedResult == NULL)
			{
				Debug::console("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				mRenderedBounds.w = textSurface->w;
				mRenderedBounds.h = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}
	}

	mRequiresRedraw = false;
}

void Text::SetScrollOffset(int x, int y)
{
	mScrollPosition.x = x;
	mScrollPosition.y = y;

	if (mScrollPosition.x + mBounds.w > mRenderedBounds.w) mScrollPosition.x = mRenderedBounds.w - mBounds.w;
	if (mScrollPosition.y + mBounds.h > mRenderedBounds.h) mScrollPosition.y = mRenderedBounds.h - mBounds.h;

	if (mScrollPosition.x < 0) mScrollPosition.x = 0;
	if (mScrollPosition.y < 0) mScrollPosition.y = 0;
}

void Text::SetColor(Color color)
{
	if (mColor != color)
	{
		mColor = color;
		SetRedraw();
	}
}

void Text::SetRedraw(bool redraw)
{
	mRequiresRedraw = mRequiresRedraw || redraw;
}
