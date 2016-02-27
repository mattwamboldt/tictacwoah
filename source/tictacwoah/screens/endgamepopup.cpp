#include "endgamepopup.h"
#include <view\ui\core\button.h>
#include "components\verticalmenu.h"
#include <app\application.h>
#include <app\event\fastdelegate.h>

EndGamePopup::EndGamePopup(TicTacLogic* logic)
{
	mLogic = logic;
}

void EndGamePopup::Create()
{
	// Create our menu
	VerticalMenu* menu = new VerticalMenu();
	Point HalfScreen = { gApp->Options.ScreenSize.x / 2, gApp->Options.ScreenSize.y / 2 };
	menu->Position(HalfScreen.x - 100, HalfScreen.y - 90 / 2);
	AddChild("menu", menu);

	// Populate the buttons
	// Play Again
	{
		Button* button = new Button(
			gApp->GetText("REPLAY"),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 28
			);

		button->Dimensions(200, 40);
		button->SetTextOffset(25, 0);
		button->SetPressHandler(fastdelegate::MakeDelegate(this, &EndGamePopup::Retry));
		button->SetFocusGainHandler(fastdelegate::MakeDelegate(menu, &VerticalMenu::OnFocusChanged));
		button->SetFocus(true);

		menu->AddChild(button);
	}

	// Back to main menu
	{
		Button* button = new Button(
			gApp->GetText("QUIT_TO_MAIN"),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 28
			);

		button->Dimensions(200, 40);
		button->SetTextOffset(25, 0);
		button->SetPressHandler(fastdelegate::MakeDelegate(this, &EndGamePopup::QuitToMain));
		button->SetFocusGainHandler(fastdelegate::MakeDelegate(menu, &VerticalMenu::OnFocusChanged));

		menu->AddChild(button);
	}

	// Add the victory or loss text
	mTitle = new Text("WWWWWWWWWWWWWW", "fonts/kaiju.ttf", 50);
	mTitle->Position(menu->X(), menu->Y() - 70);
	mTitle->Width(200);
	mTitle->SetColor(Color(0xFFFFFF));
	mTitle->HorizontalAlign(Text::CENTER);
	AddChild("title", mTitle);

	mCreated = true;
}

void EndGamePopup::Display()
{
	if (mLogic->GetWinner() == PLAYER1)
	{
		mTitle->SetText(gApp->GetText("MATCH_WIN"));
		gApp->Audio.PlaySound("audio/sfx/victory.wav");
	}
	else if (mLogic->GetWinner() == PLAYER2)
	{
		mTitle->SetText(gApp->GetText("MATCH_LOSE"));
		gApp->Audio.PlaySound("audio/sfx/loss.wav");
	}
	else
	{
		mTitle->SetText(gApp->GetText("MATCH_DRAW"));
		gApp->Audio.PlaySound("audio/sfx/draw.wav");
	}

	Screen::Display();
}

// Menu callbacks
void EndGamePopup::Retry()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	mLogic->CreateGame();
	gApp->GetHumanView()->HidePopup();
}

void EndGamePopup::QuitToMain()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ChangeScreen("MainMenu");
}
