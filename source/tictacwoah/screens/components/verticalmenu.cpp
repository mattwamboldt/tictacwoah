#include "verticalmenu.h"
#include <app\application.h>
#include <string>

VerticalMenu::VerticalMenu()
{
	mCurrentItem = 0;
	mMargin = 10;
	Dimensions(0, 0);
}

bool VerticalMenu::OnKeyPress(SDL_Keycode keycode)
{
	int previous = mCurrentItem;
	int numItems = NumChildren();

	if (keycode == SDLK_UP)
	{
		mCurrentItem = (mCurrentItem - 1 + numItems) % numItems;
	}
	else if (keycode == SDLK_DOWN)
	{
		mCurrentItem = (mCurrentItem + 1) % numItems;
	}

	if (previous != mCurrentItem)
	{
		mChildren[previous]->SetFocus(false);
		mChildren[mCurrentItem]->SetFocus(true);
		gApp->Audio.PlaySound("audio/sfx/menu.wav");
		return true;
	}

	return ScreenObjectContainer::OnKeyPress(keycode);
}

void VerticalMenu::OnFocusChanged()
{
	// Update the focused item to the one that stole focus
	// TODO: Focus management is something that should be handled better but for now this will do
	for (int i = 0; i < NumChildren(); ++i)
	{
		if (mChildren[i]->HasFocus())
		{
			mCurrentItem = i;
			gApp->Audio.PlaySound("audio/sfx/menu.wav");
			return;
		}
	}
}

void VerticalMenu::AddChild(ScreenObject* item)
{
	int numChildren = NumChildren();
	if (numChildren != 0)
	{
		item->Y(Height() + mMargin);
		Height(item->Y() + item->Height());
	}
	else
	{
		item->Y(0);
		Height(item->Height());
	}

	std::string name = "menuitem";
	name += NumChildren();
	ScreenObjectContainer::AddChild(name, item);
}
