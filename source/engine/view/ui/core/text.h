#ifndef TEXT_H
#define TEXT_H

#include "SDL/SDL_ttf.h"
#include "screenobject.h"

// TODO: SDL_TTF doesn't meet our needs here. It'd be better to use a bitmap font. Switch in the future
class Text : public ScreenObject
{
public:
	enum Align
	{
		LEFT = 0,
		CENTER,
		RIGHT,
		TOP = LEFT,
		BOTTOM = RIGHT,
	};

	Text(std::string text, std::string font, int fontSize);
	virtual ~Text();

	virtual void Render(int parentX = 0, int parentY = 0);
	virtual void Width(int width);
	virtual void Dimensions(int width, int height);
	virtual void SetColor(Color color);

	void SetText(std::string text);
	void SetFont(std::string font, int size);

	Align HorizontalAlign(){ return mHorizontalAlignment; }
	Align VerticalAlign(){ return mVerticalAlignment; }
	void HorizontalAlign(Align alignment);
	void VerticalAlign(Align alignment);

	bool WrapEnabled(){ return mWrapEnabled; }
	void SetWrap(bool enabled);

	int LineHeight();

	// Overflow settings
	void SetOverflowVisible(bool visible){ mShowOverflow = visible; }
	void SetScrollOffset(int x, int y);

private:
	std::string mContent;
	std::string mFontName;
	int mFontSize;
	TTF_Font* mFont;
	bool mWrapEnabled;
	Align mHorizontalAlignment;
	Align mVerticalAlignment;
	SDL_Texture* mRenderedResult;
	SDL_Rect mRenderedBounds;
	bool mRequiresRedraw;
	bool mShowOverflow;
	Point mScrollPosition;

	void Draw();
	void SetRedraw(bool redraw = true);
};

#endif
