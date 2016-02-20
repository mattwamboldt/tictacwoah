#ifndef SCREEN_MENU_H
#define SCREEN_MENU_H

#include <view\ui\core\screenobjectcontainer.h>

class VerticalMenu : public ScreenObjectContainer
{
public:
	bool OnKeyPress(SDL_Keycode keycode);
	void OnFocusChanged();

	virtual void AddChild(ScreenObject* item);

private:
	int mCurrentItem;
};

#endif