#include <app\input\inputinterfaces.h>

class TicTacController : public IKeyboardHandler
{
public:
	// This handles spillover events, shouldn't need to do much
	virtual bool OnKeyPress(SDL_Keycode keycode);
	virtual bool OnKeyRelease(SDL_Keycode keycode);
};
