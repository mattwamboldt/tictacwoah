#ifndef TEXTBOX_H
#define TEXTBOX_H

// TODO: Refactor to be consistent and fit better in the hierarchy of the screen
// TODO: Add setting text color

#include "SDL/SDL_ttf.h"

enum TextAlign
{
	LEFT = 0,
	CENTER,
	RIGHT
};

class TextBox
{
public:
	TextBox() : renderedResult(NULL), font(NULL) {}
	~TextBox();
	void Init(const char* messsage, TTF_Font* font, int x, int y, SDL_Color color = { 255, 255, 255, 255 }, TextAlign align = LEFT);
	void SetWrap(Uint32 width);
	void Clear();
	void SetText(const char* message);
	void SetPosition(int x, int y);
	void Render();
	int Height();
	int LineHeight();

private:
	void Realign();
	TTF_Font* font;
	SDL_Color color;
	SDL_Rect position; //This is where the text is on the screen
	SDL_Rect renderRect; //This is where the surface is drawn after alignment
	TextAlign align;
	SDL_Texture* renderedResult;
	Uint32 wrapWidth;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif
