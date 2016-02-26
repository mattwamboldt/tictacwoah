#ifndef SCREENS_GAME_H
#define SCREENS_GAME_H

#include <view\ui\screen\screen.h>
#include "..\logic\tictaclogic.h"
#include <app\event\ievent.h>
#include "components\board.h"
#include <view\ui\core\text.h>

// At first the screens are going to be all hard coded, then we'll switch to
// some generic and data driven systems later on as common stuff emerges
class GameScreen : public Screen
{
public:
	GameScreen(TicTacLogic* logic);

	virtual void Create();
	virtual void Display();

	virtual bool OnKeyPress(SDL_Keycode keycode);

	// Event handlers
	void OnMatchComplete(IEvent* eventData);
	void OnLine(IEvent* eventData);
	void OnLineMerge(IEvent* eventData);
	void OnScoreChange(IEvent* eventData);
	void OnCreateGame(IEvent* eventData);

private:
	// TODO: Remove this direct reference if possible
	TicTacLogic* mLogic;
	Board* mBoard;
	Text* mP1Score;
	Text* mP2Score;
};

#endif
