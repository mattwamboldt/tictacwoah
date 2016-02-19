#ifndef BUTTON_H
#define BUTTON_H

#include "screenobjectcontainer.h"
#include <app\event\fastdelegate.h>
#include "image.h"
#include "text.h"

class Button;

typedef fastdelegate::FastDelegate0<> ButtonHandler;

// TODO: Eventually the button will be more useful as a generic thing
// I mean once this is all scripting based none of that matters, but anyway
// For now a button is hard a set of contents and actions.
class Button : public ScreenObject
{
public:
	Button(std::string text, std::string backing, std::string activebacking, std::string font, int fontSize);

	virtual void Render(int parentX = 0, int parentY = 0);

	virtual void Width(int width);
	virtual void Height(int height);
	virtual void Dimensions(int width, int height);

	virtual bool OnKeyPress(SDL_Keycode keycode);
	virtual bool OnKeyRelease(SDL_Keycode keycode);

	virtual bool OnPointerMove(int x, int y);
	virtual bool OnPointerButtonPress(int x, int y, Uint8 button);
	virtual bool OnPointerButtonRelease(int x, int y, Uint8 button);

	virtual bool OnButtonPress(Uint8 button);
	virtual bool OnButtonRelease(Uint8 button);

	virtual void SetPressHandler(ButtonHandler handler);
	virtual void SetFocusGainHandler(ButtonHandler handler);
	virtual void SetFocusLostHandler(ButtonHandler handler);

	void SetTextOffset(int x, int y);

protected:
	ButtonHandler mOnPress;
	ButtonHandler mOnFocusGained;
	ButtonHandler mOnFocusLost;

	Image mBacking;
	Image mBackingActive;
	Text mText;
};

#endif
