#include "difficultypopup.h"

#include <app\application.h>
#include <app\debug\logging.h>
#include <view\ui\core\image.h>
#include <view\ui\core\button.h>
#include "components\verticalmenu.h"

#include "..\tictacwoahapp.h"
#include "..\logic\tictaclogic.h"

void DifficultyPopup::Create()
{
	if (mCreated)
	{
		Debug::console("Attempting to create existing screen.");
		return;
	}

	// Resize the popup and position it in the middle of the screen
	// For now the whole popup is self contained, but in the future we may want a background fade over buttons and whatnot
	Dimensions(400, 500);
	Point HalfScreen = { gApp->Options.ScreenSize.x / 2, gApp->Options.ScreenSize.y / 2 };
	Position(HalfScreen.x - Width() / 2, HalfScreen.y - Height() / 2);

	// Create our menu
	VerticalMenu* difficultyMenu = new VerticalMenu();
	difficultyMenu->Position(100, 100);
	AddChild("difficultymenu", difficultyMenu);

	// Populate the buttons
	{
		Button* easybutton = new Button(
			gApp->GetText("DIFFICULTY_EASY"),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 28
			);

		easybutton->Dimensions(200, 40);
		easybutton->SetTextOffset(25, 0);
		easybutton->SetPressHandler(fastdelegate::MakeDelegate(this, &DifficultyPopup::StartEasy));
		easybutton->SetFocusGainHandler(fastdelegate::MakeDelegate(difficultyMenu, &VerticalMenu::OnFocusChanged));
		easybutton->SetFocus(true);

		difficultyMenu->AddChild(easybutton);
	}

	{
		Button* mediumbutton = new Button(
			gApp->GetText("DIFFICULTY_MEDIUM"),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 28
			);

		mediumbutton->Dimensions(200, 40);
		mediumbutton->SetTextOffset(25, 0);
		mediumbutton->SetPressHandler(fastdelegate::MakeDelegate(this, &DifficultyPopup::StartMedium));
		mediumbutton->SetFocusGainHandler(fastdelegate::MakeDelegate(difficultyMenu, &VerticalMenu::OnFocusChanged));

		difficultyMenu->AddChild(mediumbutton);
	}

	{
		Button* hardbutton = new Button(
			gApp->GetText("DIFFICULTY_HARD"),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 28
			);

		hardbutton->Dimensions(200, 40);
		hardbutton->SetTextOffset(25, 0);
		hardbutton->SetPressHandler(fastdelegate::MakeDelegate(this, &DifficultyPopup::StartHard));
		hardbutton->SetFocusGainHandler(fastdelegate::MakeDelegate(difficultyMenu, &VerticalMenu::OnFocusChanged));

		difficultyMenu->AddChild(hardbutton);
	}

	mCreated = true;
}

void DifficultyPopup::StartEasy()
{
	TicTacLogic& logic = ((TicTacWoahApp*)gApp)->logic;
	logic.SetDifficulty(TicTacLogic::EASY);
	logic.CreateGame();
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ChangeScreen("GameScreen");
}

void DifficultyPopup::StartMedium()
{
	TicTacLogic& logic = ((TicTacWoahApp*)gApp)->logic;
	logic.SetDifficulty(TicTacLogic::MEDIUM);
	logic.CreateGame();
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ChangeScreen("GameScreen");
}

void DifficultyPopup::StartHard()
{
	TicTacLogic& logic = ((TicTacWoahApp*)gApp)->logic;
	logic.SetDifficulty(TicTacLogic::HARD);
	logic.CreateGame();
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ChangeScreen("GameScreen");
}
