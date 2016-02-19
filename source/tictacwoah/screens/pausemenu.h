#ifndef SCREENS_PAUSEMENU_H
#define SCREENS_PAUSEMENU_H

#include <view\ui\screen\screen.h>

// At first the screens are going to be all hard coded, then we'll switch to
// some generic and data driven systems later on as common stuff emerges
class PauseMenu : public Screen
{
public:
	virtual void Create();

	// Menu callbacks
	void Resume();
	void Volume(float value);
	void SFX(float value);
	void Music(float value);
	void QuitToMain();
	void Quit();

	virtual bool IsModal(){ return true; }

	enum PauseMenuItem
	{
		PauseMenu_Resume = 0,
		PauseMenu_Volume,
		PauseMenu_SFX,
		PauseMenu_Music,
		PauseMenu_QuitToMain,
		PauseMenu_Quit,
		NUM_PAUSEMENUITEMS
	};
};

#endif
