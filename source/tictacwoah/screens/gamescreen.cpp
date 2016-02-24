#include "gamescreen.h"
#include "components\board.h"
#include <view\ui\core\image.h>
#include <app\application.h>
#include "../events/gameevents.h"
#include <app/event/eventmanager.h>

GameScreen::GameScreen(TicTacLogic* logic)
{
	mLogic = logic;
}

void GameScreen::Create()
{
	Image* background = new Image();
	background->SetTexture("images/background/basicmode.png");
	background->Dimensions(Width(), Height());
	AddChild("background", background);

	// Currently the logic will render until we move that into a new component
	Board* board = new Board(mLogic);
	board->Dimensions(500, 500);
	board->Position((Width() - board->Width()) / 2, (Height() - board->Height()) / 2);
	AddChild("board", board);

	// Register for events
	EventManager::Get()->AddListener(fastdelegate::MakeDelegate(this, &GameScreen::OnMatchComplete), MatchCompleteEvent::Type);
}

void GameScreen::OnMatchComplete(IEvent* eventData)
{
	gApp->GetHumanView()->ShowPopup("EndGamePopup");
}

bool GameScreen::OnKeyPress(SDL_Keycode keycode)
{
	if (keycode == SDLK_ESCAPE)
	{
		gApp->GetHumanView()->ShowPopup("PauseMenu");
		return true;
	}

	return Screen::OnKeyPress(keycode);
}

void GameScreen::Display()
{
	Screen::Display();
	gApp->Audio.PlayMusic("audio/music/captaincrunch.ogg");
}
