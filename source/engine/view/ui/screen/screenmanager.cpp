#include "screenmanager.h"
#include <app\debug\logging.h>

void ScreenManager::Update(float deltaTime)
{
	// For now we update all screens, but may decide to pause
	// all screens later
	for (unsigned int i = 0; i < mScreenStack.size(); ++i)
	{
		mScreenStack[i]->Update();
	}
}

void ScreenManager::Render()
{
	// Render from back to front
	for (unsigned int i = 0; i < mScreenStack.size(); ++i)
	{
		mScreenStack[i]->Render();
	}
}

void ScreenManager::AddScreen(const char* screenName, Screen* screen)
{
	if (mScreenList.find(screenName) != mScreenList.end())
	{
		// Duplicate screen, don't add it
		Debug::console("Attempting to add Duplicate Screen: %s", screenName);
		return;
	}

	mScreenList[screenName] = screen;
}

//TODO: This should call Hide on the stack in reverse order, then display on the new one
// for now we'll just hide/display without the callback business
void ScreenManager::ChangeScreen(const char* screenName)
{
	for (unsigned int i = 0; i < mScreenStack.size(); ++i)
	{
		mScreenStack[i]->Hide();
	}
	
	mScreenStack.clear();
	auto screenEntry = mScreenList.find(screenName);
	if (screenEntry != mScreenList.end())
	{
		Screen* screen = screenEntry->second;
		mScreenStack.push_back(screen);

		if (!screen->IsCreated())
		{
			screen->Create();
		}

		screen->Display();
	}
	else
	{
		Debug::console("Failed to find screen: %s", screenName);
	}
}

void ScreenManager::ShowPopup(const char* popupName)
{
	auto popupEntry = mScreenList.find(popupName);
	if (popupEntry != mScreenList.end())
	{
		Screen* popup = popupEntry->second;
		mScreenStack.push_back(popup);

		if (!popup->IsCreated())
		{
			popup->Create();
		}

		popup->Display();
	}
	else
	{
		Debug::console("Failed to find popup: %s", popupName);
	}
}

void ScreenManager::HidePopup()
{
	if (mScreenStack.size() > 1)
	{
		Screen* popup = mScreenStack.back();
		popup->Hide();
		mScreenStack.pop_back();
	}
}

bool ScreenManager::OnKeyPress(SDL_Keycode keycode)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnKeyPress(keycode))
		{
			return true;
		}
	}

	return false;
}

bool ScreenManager::OnKeyRelease(SDL_Keycode keycode)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnKeyRelease(keycode))
		{
			return true;
		}
	}

	return false;
}

bool ScreenManager::OnPointerMove(int x, int y)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnPointerMove(x, y))
		{
			return true;
		}
	}

	return false;
}

bool ScreenManager::OnPointerButtonPress(int x, int y, Uint8 button)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnPointerButtonPress(x, y, button))
		{
			return true;
		}
	}

	return false;
}

bool ScreenManager::OnPointerButtonRelease(int x, int y, Uint8 button)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnPointerButtonRelease(x, y, button))
		{
			return true;
		}
	}

	return false;
}

bool ScreenManager::OnButtonPress(Uint8 button)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnButtonPress(button))
		{
			return true;
		}
	}

	return false;
}

bool ScreenManager::OnButtonRelease(Uint8 button)
{
	for (auto it = mScreenStack.rbegin(); it != mScreenStack.rend(); ++it)
	{
		if ((*it)->OnButtonRelease(button))
		{
			return true;
		}
	}

	return false;
}
