#ifndef SCREENS_GAME_H
#define SCREENS_GAME_H

#include <view\ui\screen\screen.h>
#include "..\logic\tictaclogic.h"

// At first the screens are going to be all hard coded, then we'll switch to
// some generic and data driven systems later on as common stuff emerges
class GameScreen : public Screen
{
public:
	GameScreen(TicTacLogic* logic);

	virtual void Create();

	virtual bool OnKeyPress(SDL_Keycode keycode);

private:
	// TODO: Remove this direct reference if possible
	TicTacLogic* mLogic;
};

#endif
