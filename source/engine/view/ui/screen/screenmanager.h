#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <view\ui\screen\screen.h>

class ScreenManager : public IKeyboardHandler, public IPointerHandler, public IGamepadHandler
{
public:
	void Update(float deltaTime);
	void Render();

	void AddScreen(const char* name, Screen* screen);
	void ChangeScreen(const char* screenName);
	void ShowPopup(const char* popupName);
	void HidePopup();

	virtual bool OnKeyPress(SDL_Keycode keycode);
	virtual bool OnKeyRelease(SDL_Keycode keycode);

	virtual bool OnPointerMove(int x, int y);
	virtual bool OnPointerButtonPress(int x, int y, Uint8 button);
	virtual bool OnPointerButtonRelease(int x, int y, Uint8 button);

	virtual bool OnButtonPress(Uint8 button);
	virtual bool OnButtonRelease(Uint8 button);

private:
	// A map of all of the available screens
	std::unordered_map<const char*, Screen*> mScreenList;

	// The active set of screens. Allows multiple screens to sit on top of one another
	std::vector<Screen*> mScreenStack;

	// Allows back button functionality
	std::vector<Screen*> mScreenHistory;
};

#endif
