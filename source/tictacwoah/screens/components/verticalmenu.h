#ifndef SCREEN_MENU_H
#define SCREEN_MENU_H

#include <view\ui\core\screenobjectcontainer.h>

class VerticalMenu : public ScreenObjectContainer
{
public:
	VerticalMenu();
	bool OnKeyPress(SDL_Keycode keycode);
	void OnFocusChanged();

	virtual void AddChild(ScreenObject* item);

	void SetMargin(int val){ mMargin = val; }

private:
	int mCurrentItem;
	int mMargin;
};

#endif