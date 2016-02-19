#include "tictacwoahapp.h"

bool TicTacWoahApp::CreateLogicAndViews()
{
	mView = new TicTacWoahView();
	return true;
}

const char* TicTacWoahApp::Name()
{
	return "Tic Tac WOAH!";
}
