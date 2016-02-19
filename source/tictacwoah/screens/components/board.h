#ifndef BOARD_H
#define BOARD_H

#include <view\ui\core\screenobject.h>
#include "..\..\logic\tictaclogic.h"

// This is a hard coded tic tac toe board, We'll be changing it as
// time goes on and maybe some genric stuff can get pulled later

class Board : public ScreenObject
{
public:
	Board(TicTacLogic* logic);

	virtual void Render(int parentX = 0, int parentY = 0);

	virtual bool OnKeyPress(SDL_Keycode keycode);
	virtual bool OnKeyRelease(SDL_Keycode keycode);

	virtual bool OnPointerMove(int x, int y);
	virtual bool OnPointerButtonPress(int x, int y, Uint8 button);
	virtual bool OnPointerButtonRelease(int x, int y, Uint8 button);

	virtual bool OnButtonPress(Uint8 button);
	virtual bool OnButtonRelease(Uint8 button);

private:
	void UpdatePointer(int x, int y);

	TicTacLogic* mLogic;

	SDL_Texture* mFadeTexture;
	SDL_Texture* mPlayer1Texture;
	SDL_Texture* mPlayer2Texture;

	// Where the mouse is on the board;
	Point mPointerCoords;
};

#endif