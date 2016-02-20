#include "pausemenu.h"
#include <app\application.h>
#include <app\resource\resourcemanager.h>
#include <app\debug\logging.h>
#include <view\ui\core\image.h>
#include <view\ui\core\button.h>
#include "components\verticalmenu.h"

const char* pauseoptionnames[] = {
	"RESUME",
	"OPT_MASTER_VOLUME",
	"OPT_SFX_VOLUME",
	"OPT_MUSIC_VOLUME",
	"QUIT_TO_MAIN",
	"QUIT"
};

void PauseMenu::Create()
{
	if (mCreated)
	{
		Debug::console("Attempting to create existing screen.");
		return;
	}

	// First create the background
	Image* background = new Image();
	background->SetTexture("images/fade.png");
	background->Dimensions(Width(), Height());
	AddChild("background", background);

	// Then create our menu
	VerticalMenu* menu = new VerticalMenu();
	// TODO: Some Layout methods would be nice...
	menu->Position((Width() - 200) / 2, (Height() - 50 * NUM_PAUSEMENUITEMS) / 2);
	AddChild("pausemenu", menu);

	// Add our menu items, these are offset along an angle
	Point position = { 0, 0 };

	for (int i = 0; i < NUM_PAUSEMENUITEMS; ++i)
	{
		Button* button = new Button(
			gApp->GetText(pauseoptionnames[i]),
			"images/inactivebutton.png",
			"images/activebutton.png",
			"fonts/kaiju.ttf", 20
			);

		button->Dimensions(200, 40);
		button->SetTextOffset(25, 0);
		button->Position(position.x, position.y);

		position.y += 50;

		// Every menu button has a callback
		switch (i)
		{
		case PauseMenu_Resume:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &PauseMenu::Resume));
			break;

		case PauseMenu_QuitToMain:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &PauseMenu::QuitToMain));
			break;

		case PauseMenu_Quit:
			button->SetPressHandler(fastdelegate::MakeDelegate(this, &PauseMenu::Quit));
			break;
		}

		// Focus management
		button->SetFocus(i == 0);
		button->SetFocusGainHandler(fastdelegate::MakeDelegate(menu, &VerticalMenu::OnFocusChanged));

		menu->AddChild(button);
	}

	mCreated = true;
}

void PauseMenu::Resume()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->HidePopup();
}

void PauseMenu::Volume(float value)
{

}

void PauseMenu::SFX(float value)
{

}

void PauseMenu::Music(float value)
{

}

void PauseMenu::QuitToMain()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	gApp->GetHumanView()->ChangeScreen("MainMenu");
}

void PauseMenu::Quit()
{
	gApp->Audio.PlaySound("audio/sfx/select.wav");
	SDL_Event ev;
	ev.type = SDL_QUIT;
	SDL_PushEvent(&ev);
}
