#include "button.h"

Button::Button(std::string text, std::string backing, std::string activebacking, std::string font, int fontSize)
	: mBacking(backing.c_str()), mBackingActive(activebacking.c_str()), mText(text, font, fontSize)
{
	Dimensions(mBacking.Width(), mBacking.Height());
}

void Button::Render(int parentX, int parentY)
{
	Point position = { parentX + mBounds.x, parentY + mBounds.y };
	if (HasFocus())
	{
		mBackingActive.Render(position.x, position.y);
	}
	else
	{
		mBacking.Render(position.x, position.y);
	}
	
	mText.Render(position.x, position.y);
}

void Button::Width(int width)
{
	ScreenObject::Width(width);
	mText.Width(width);
	mBacking.Width(width);
	mBackingActive.Width(width);
}

void Button::Height(int height)
{
	ScreenObject::Height(height);
	mText.Height(height);
	mBacking.Height(height);
	mBackingActive.Height(height);
}

void Button::Dimensions(int width, int height)
{
	ScreenObject::Dimensions(width, height);
	mText.Dimensions(width, height);
	mBacking.Dimensions(width, height);
	mBackingActive.Dimensions(width, height);
}

void Button::SetTextOffset(int x, int y)
{
	mText.Position(x, y);
}

bool Button::OnKeyPress(SDL_Keycode keycode)
{
	if (HasFocus() && keycode == SDLK_RETURN && mOnPress)
	{
		mOnPress();
		return true;
	}

	return false;
}

bool Button::OnKeyRelease(SDL_Keycode keycode)
{
	return false;
}

bool Button::OnPointerMove(int x, int y)
{
	bool hadFocus = HasFocus();
	SetFocus(x >= mBounds.x && x <= mBounds.w + mBounds.x && y >= mBounds.y && y <= mBounds.h + mBounds.y);
	if (hadFocus && !HasFocus())
	{
		if (mOnFocusLost) mOnFocusLost();
		return true;
	}
	else if (!hadFocus && HasFocus())
	{
		if (mOnFocusGained) mOnFocusGained();
		return true;
	}

	return false;
}

bool Button::OnPointerButtonPress(int x, int y, Uint8 button)
{
	OnPointerMove(x, y);
	if (HasFocus() && button == SDL_BUTTON_LEFT && mOnPress)
	{
		mOnPress();
		return true;
	}

	return false;
}

bool Button::OnPointerButtonRelease(int x, int y, Uint8 button)
{
	return false;
}

bool Button::OnButtonPress(Uint8 button)
{
	if (HasFocus() && button == SDL_CONTROLLER_BUTTON_A && mOnPress)
	{
		mOnPress();
		return true;
	}

	return false;
}

bool Button::OnButtonRelease(Uint8 button)
{
	return false;
}

void Button::SetPressHandler(ButtonHandler handler)
{
	mOnPress = handler;
}

void Button::SetFocusGainHandler(ButtonHandler handler)
{
	mOnFocusGained = handler;
}

void Button::SetFocusLostHandler(ButtonHandler handler)
{
	mOnFocusLost = handler;
}
