#include "screen.h"
#include <app\application.h>

Screen::Screen() : mCreated(false)
{
	Dimensions(gApp->Options.ScreenSize.x, gApp->Options.ScreenSize.y);
	Visible(false);
	Enabled(false);
}

void Screen::Display()
{
	Visible(true);

	//TODO:Handle transition in animations with callback
	OnDisplayComplete();
}

void Screen::OnDisplayComplete()
{
	Enabled(true);
}

void Screen::Hide()
{
	Enabled(false);

	// TODO: Handle transition out animations with callback
	OnHidden();
}

void Screen::OnHidden()
{
	Visible(false);
}
