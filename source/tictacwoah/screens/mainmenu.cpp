#include "mainmenu.h"
#include <app\application.h>
#include <app\resource\resourcemanager.h>
#include <app\debug\logging.h>
#include <view\ui\core\image.h>
#include <view\ui\core\button.h>
#include "components\verticalmenu.h"

#include "..\tictacwoahapp.h"
#include "..\logic\tictaclogic.h"

const char* menuoptionnames[] = {
	"MODE_BASIC",
	"MODE_RECURSION",
	"MODE_BIGBOARD",
	"MODE_NINJA",
	"OPTIONS",
	"QUIT"
};

void MainMenu::Create()
{
	if (mCreated)
	{
		Debug::console("Attempting to create existing screen.");
		return;
	}

	// First create the background
	Image* background = new Image();
	background->SetTexture("images/background/mainmenu.png");
	background->Dimensions(gApp->Options.ScreenSize.x, gApp->Options.ScreenSize.y);
	AddChild("background", background);

	// Then create our menu
	VerticalMenu* mainMenu = new VerticalMenu();
	mainMenu->Position(80, 50);
	AddChild("mainmenu", mainMenu);

	// Add our menu items, these are offset along an angle
	int xPosition = 0;

	for (int i = 0; i < NUM_MAINMENUITEMS; ++i)
	{
		Button* button = new Button(
			gApp->GetText(menuoptionnames[i]),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 28
			);

		button->Dimensions(200, 40);
		button->SetTextOffset(35, 0);
		button->X(xPosition);
		xPosition -= 7;

		// Every menu button has a callback
		switch (i)
		{
		case MainMenu_Basic:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &MainMenu::Basic));
			break;

		case MainMenu_Recursion:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &MainMenu::Recursion));
			break;

		case MainMenu_BigBoard:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &MainMenu::BigBoard));
			break;

		case MainMenu_Ninja:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &MainMenu::Ninja));
			break;

		case MainMenu_Options:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &MainMenu::Options));
			break;

		case MainMenu_Quit:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &MainMenu::Quit));
			break;
		}

		// Focus management
		button->SetFocus(i == 0);
		button->SetFocusGainHandler(fastdelegate::MakeDelegate(mainMenu, &VerticalMenu::OnFocusChanged));

		mainMenu->AddChild(button);
	}

	mCreated = true;
}

void MainMenu::Display()
{
	Screen::Display();
	gApp->Audio.PlayMusic("audio/music/calmdown.ogg");
}

void MainMenu::Basic()
{
	// Set the mode to basic and show the difficulty popup
	((TicTacWoahApp*)gApp)->logic.SetMode(TicTacLogic::BASIC);
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ShowPopup("DifficultyPopup");
}

void MainMenu::Recursion()
{
	// Set the mode to big board and show the difficulty popup
	((TicTacWoahApp*)gApp)->logic.SetMode(TicTacLogic::RECURSION);
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ShowPopup("DifficultyPopup");
}

void MainMenu::BigBoard()
{
	// Set the mode to big board and show the difficulty popup
	((TicTacWoahApp*)gApp)->logic.SetMode(TicTacLogic::BIGBOARD);
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ShowPopup("DifficultyPopup");
}

void MainMenu::Ninja()
{
	// Set the mode to ninja and show the difficulty popup
	((TicTacWoahApp*)gApp)->logic.SetMode(TicTacLogic::NINJA);
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ShowPopup("DifficultyPopup");
}

void MainMenu::Options()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	//TODO: Change to the options screen
	(*this)["mainmenu"]->Move(rand() % 500, rand() % 500, 200);
}

void MainMenu::Quit()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	SDL_Event ev;
	ev.type = SDL_QUIT;
	SDL_PushEvent(&ev);
}
