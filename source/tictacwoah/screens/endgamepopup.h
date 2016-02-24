#ifndef SCREENS_ENDGAMEPOPUP_H
#define SCREENS_ENDGAMEPOPUP_H

#include <view\ui\screen\screen.h>
#include <view\ui\core\text.h>
#include "..\logic\tictaclogic.h"

// This is the screen that shows up at the end of the game
class EndGamePopup : public Screen
{
public:
	EndGamePopup(TicTacLogic* logic);
	virtual void Create();
	virtual void Display();

	// Menu callbacks
	void Retry();
	void QuitToMain();

	virtual bool IsModal(){ return true; }

private:
	// TODO: Remove this direct reference if possible
	TicTacLogic* mLogic;
	Text* mTitle;
};

#endif
