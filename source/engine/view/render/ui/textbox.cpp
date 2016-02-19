#include <app/application.h>
#include "textbox.h"
#include <cstdio>

void TextBox::Init(const char* messsage, TTF_Font* font, int x, int y, SDL_Color color, TextAlign align)
{
	wrapWidth = 0;
	this->font = font;
	this->color = color;
	position.x = x;
	position.y = y;
	this->align = align;
	SetText(messsage);
}

void TextBox::Clear()
{
	if (renderedResult)
	{
		SDL_DestroyTexture(renderedResult);
		renderedResult = NULL;
	}
}

TextBox::~TextBox()
{
	Clear();
}

void TextBox::Realign()
{
	if (renderedResult)
	{
		renderRect.x = position.x;
		renderRect.y = position.y;

		if (align == RIGHT)
		{
			renderRect.x -= mWidth;
		}
		else if (align == CENTER)
		{
			renderRect.x -= (mWidth / 2);
		}
	}
}

void TextBox::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
	Realign();
}

void TextBox::SetWrap(Uint32 width)
{
	wrapWidth = width;
}

void TextBox::SetText(const char* message)
{
	Clear();

	if (font)
	{
		//Render text surface
		SDL_Surface* textSurface = NULL;

		if (wrapWidth)
		{
			textSurface = TTF_RenderText_Blended_Wrapped(font, message, color, wrapWidth);
		}
		else
		{
			textSurface = TTF_RenderText_Blended(font, message, color);
		}

		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			renderedResult = SDL_CreateTextureFromSurface(gApp->Renderer(), textSurface);
			if (renderedResult == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				renderRect.w = textSurface->w;
				renderRect.h = textSurface->h;
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		Realign();
	}
}

void TextBox::Render()
{
	if (renderedResult)
	{
		SDL_RenderCopy(gApp->Renderer(), renderedResult, NULL, &renderRect);
	}
}

int TextBox::Height()
{
	if (renderedResult)
	{
		return mHeight;
	}

	return 0;
}

int TextBox::LineHeight()
{
	return TTF_FontHeight(font);
}