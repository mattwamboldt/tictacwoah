#include "tictaccontroller.h"

// This handles spillover events, shouldn't need to do much
bool TicTacController::OnKeyPress(SDL_Keycode keycode)
{
	return false;
}

bool TicTacController::OnKeyRelease(SDL_Keycode keycode)
{
	return false;
}