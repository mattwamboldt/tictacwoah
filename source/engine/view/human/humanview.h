#ifndef HUMANVIEW_H
#define HUMANVIEW_H

#include <view\igameview.h>
#include <app\input\inputinterfaces.h>
#include <view\ui\screen\screenmanager.h>

class HumanView : public IGameView
{
public:
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual bool HandleInput(const SDL_Event& msg);

	void AddScreen(const char* name, Screen* screen);
	void ChangeScreen(const char* screenName);
	void ShowPopup(const char* popupName);
	void HidePopup();

	void SetKeyHandler(IKeyboardHandler* keyboardHandler){ mKeyboardHandler = keyboardHandler; }
	void SetPointerHandler(IPointerHandler* pointerHandler){ mPointerHandler = pointerHandler; }
	void SetGamepadHandler(IGamepadHandler* gamepadHandler){ mGamepadHandler = gamepadHandler; }

protected:
	// TODO: Need a better way to accessn screen management functions without adding a bunch of interface shim garbage
	ScreenManager mScreenManager;

	IKeyboardHandler* mKeyboardHandler;
	IPointerHandler* mPointerHandler;
	IGamepadHandler* mGamepadHandler;
};

#endif