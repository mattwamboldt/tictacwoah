#ifndef SCREENS_MAINMENU_H
#define SCREENS_MAINMENU_H

#include <view\ui\screen\screen.h>

// At first the screens are going to be all hard coded, then we'll switch to
// some generic and data driven systems later on as common stuff emerges
class MainMenu : public Screen
{
public:
	virtual void Create();
	virtual void Display();

	// Menu callbacks
	void Basic();
	void Recursion();
	void BigBoard();
	void Ninja();
	void Options();
	void Quit();

	enum MainMenuItem
	{
		MainMenu_Basic = 0,
		MainMenu_Recursion,
		MainMenu_BigBoard,
		MainMenu_Ninja,
		MainMenu_Options,
		MainMenu_Quit,
		NUM_MAINMENUITEMS
	};
};

#endif
