#include "humanview.h"

void HumanView::Update(float deltaTime)
{
	mScreenManager.Update(deltaTime);
}

void HumanView::Render()
{
	mScreenManager.Render();
}

bool HumanView::HandleInput(const SDL_Event& msg)
{
	// This is gross, never should have used the GCC arch for this, at least not without committing to the rest of it
	if (msg.type == SDL_KEYDOWN)
	{
		if (mScreenManager.OnKeyPress(msg.key.keysym.sym)) return true;
		if (mKeyboardHandler) return mKeyboardHandler->OnKeyPress(msg.key.keysym.sym);
	}
	else if (msg.type == SDL_KEYUP)
	{
		return mScreenManager.OnKeyRelease(msg.key.keysym.sym);
		if (mKeyboardHandler) return mKeyboardHandler->OnKeyRelease(msg.key.keysym.sym);
	}
	else if (msg.type == SDL_MOUSEMOTION)
	{
		return mScreenManager.OnPointerMove(msg.motion.x, msg.motion.y);
		if (mPointerHandler) return mPointerHandler->OnPointerMove(msg.motion.x, msg.motion.y);
	}
	else if (msg.type == SDL_MOUSEBUTTONDOWN)
	{
		return mScreenManager.OnPointerButtonPress(msg.button.x, msg.button.y, msg.button.button);
		if (mPointerHandler) return mPointerHandler->OnPointerButtonPress(msg.button.x, msg.button.y, msg.button.button);
	}
	else if (msg.type == SDL_MOUSEBUTTONUP)
	{
		return mScreenManager.OnPointerButtonRelease(msg.button.x, msg.button.y, msg.button.button);
		if (mPointerHandler) return mPointerHandler->OnPointerButtonRelease(msg.button.x, msg.button.y, msg.button.button);
	}
	else if (msg.type == SDL_CONTROLLERBUTTONDOWN)
	{
		return mScreenManager.OnButtonPress(msg.cbutton.button);
		if (mGamepadHandler) return mGamepadHandler->OnButtonPress(msg.cbutton.button);
	}
	else if (msg.type == SDL_CONTROLLERBUTTONUP)
	{
		return mScreenManager.OnButtonRelease(msg.cbutton.button);
		if (mGamepadHandler) return mGamepadHandler->OnButtonRelease(msg.cbutton.button);
	}

	return false;
}

void HumanView::AddScreen(const char* name, Screen* screen)
{
	mScreenManager.AddScreen(name, screen);
}

void HumanView::ChangeScreen(const char* screenName)
{
	mScreenManager.ChangeScreen(screenName);
}

void HumanView::ShowPopup(const char* popupName)
{
	mScreenManager.ShowPopup(popupName);
}

void HumanView::HidePopup()
{
	mScreenManager.HidePopup();
}