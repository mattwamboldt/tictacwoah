#include "gamescreen.h"
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
	mBoard = new Board(mLogic);
	mBoard->Dimensions(500, 500);
	mBoard->Position((Width() - mBoard->Width()) / 2, (Height() - mBoard->Height()) / 2);
	AddChild("board", mBoard);

	mP1Score = new Text("PLAYER 1: 0", "fonts/kaiju.ttf", 20);
	mP1Score->Position(50, 50);
	mP1Score->SetColor(Color(0xFFFFFFFF));
	AddChild("P1Score", mP1Score);
	mP2Score = new Text("PLAYER 2: 0", "fonts/kaiju.ttf", 20);
	mP2Score->Position(Width() - 300, 50);
	mP2Score->SetColor(Color(0xFFFFFFFF));
	AddChild("P2Score", mP2Score);

	// Register for events
	EventManager::Get()->AddListener(fastdelegate::MakeDelegate(this, &GameScreen::OnMatchComplete), MatchCompleteEvent::Type);
	EventManager::Get()->AddListener(fastdelegate::MakeDelegate(this, &GameScreen::OnLine), LineEvent::Type);
	EventManager::Get()->AddListener(fastdelegate::MakeDelegate(this, &GameScreen::OnLineMerge), LineMergeEvent::Type);
	EventManager::Get()->AddListener(fastdelegate::MakeDelegate(this, &GameScreen::OnScoreChange), ScoreChangeEvent::Type);
	EventManager::Get()->AddListener(fastdelegate::MakeDelegate(this, &GameScreen::OnCreateGame), CreateGameEvent::Type);
}

void GameScreen::OnMatchComplete(IEvent* eventData)
{
	gApp->GetHumanView()->ShowPopup("EndGamePopup");
}

void GameScreen::OnLine(IEvent* eventData)
{
	LineEvent* lineEvent = (LineEvent*)eventData;
	if (lineEvent->Flag == OBJECT_CREATED)
	{
		mBoard->AddLine(lineEvent->LineData, lineEvent->GridId != 0);
	}
	else if (lineEvent->Flag == OBJECT_MODIFIED)
	{
		mBoard->ChangeLine(lineEvent->LineData);
	}
	else if (lineEvent->Flag == OBJECT_DELETED)
	{
		mBoard->RemoveLine(lineEvent->LineData.id);
	}
}

void GameScreen::OnLineMerge(IEvent* eventData)
{
	LineMergeEvent* mergeEvent = (LineMergeEvent*)eventData;
	for (unsigned int i = 0; i < mergeEvent->ExistingLineIds.size(); ++i)
	{
		mBoard->RemoveLine(mergeEvent->ExistingLineIds[i]);
	}

	mBoard->AddLine(mergeEvent->LineData);
}

void GameScreen::OnScoreChange(IEvent* eventData)
{
	ScoreChangeEvent* scoreEvent = (ScoreChangeEvent*)eventData;
	if (scoreEvent->Player == PLAYER1)
	{
		mP1Score->SetText(std::string("PLAYER 1: ") + std::to_string(scoreEvent->Score));
	}
	else
	{
		mP2Score->SetText(std::string("PLAYER 2: ") + std::to_string(scoreEvent->Score));
	}
}

void GameScreen::OnCreateGame(IEvent* eventData)
{
	mP1Score->SetText("PLAYER 1: 0");
	mP2Score->SetText("PLAYER 2: 0");
	mBoard->Init();

	if (mLogic->GetMode() == TicTacLogic::BIGBOARD || mLogic->GetMode() == TicTacLogic::NINJA)
	{
		mP1Score->Visible(true);
		mP2Score->Visible(true);
	}
	else
	{
		mP1Score->Visible(false);
		mP2Score->Visible(false);
	}
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
	mBoard->Init();
	if (mLogic->GetMode() == TicTacLogic::BIGBOARD || mLogic->GetMode() == TicTacLogic::NINJA)
	{
		mP1Score->Visible(true);
		mP2Score->Visible(true);
	}
	else
	{
		mP1Score->Visible(false);
		mP2Score->Visible(false);
	}

	gApp->Audio.PlayMusic("audio/music/captaincrunch.ogg");
}
