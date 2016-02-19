#include "tictacwoahapp.h"
#include <app\application.h>

#include "screens\mainmenu.h"
#include "screens\difficultypopup.h"
#include "screens\gamescreen.h"
#include "screens\pausemenu.h"

TicTacWoahView::TicTacWoahView()
{
	mScreenManager.AddScreen("MainMenu", new MainMenu());
	mScreenManager.AddScreen("DifficultyPopup", new DifficultyPopup());
	mScreenManager.AddScreen("PauseMenu", new PauseMenu());
	mScreenManager.AddScreen("GameScreen", new GameScreen(&(((TicTacWoahApp*)gApp)->logic ))); // I know...
	mScreenManager.ChangeScreen("MainMenu");
}
