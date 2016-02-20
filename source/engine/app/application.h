/*
The application contains everything needed for interfacing with low level systems.
This includes the string database, renderer, audio, file system, init/shutdown, core algos and data structures...
Basically anything not related to the game itself
*/

#ifndef APPLICATION
#define APPLICATION

#include "SDL/SDL.h"
#include "../logic/igamelogic.h"
#include "../view/igameview.h"
#include "../view/human/humanview.h"
#include "options/options.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "event\eventmanager.h"
#include "../view/ui/core/text.h"
#include "audio\audiosystem.h"

enum Language
{
	ENGLISH = 0,
	NUM_LANGUAGES,
	INVALID_LANG = -1,
	DEFAULT_LANG = ENGLISH
};

class Application
{
public:
	Application();

	bool Init();
	void Run();
	void Shutdown();

	virtual bool CreateLogicAndViews() = 0;
	virtual const char* Name() = 0;

	inline SDL_Renderer* Renderer() { return mRenderer; }

	const char* GetText(std::string id);
	bool SetLanguage(Language language);

	GameOptions Options;
	AudioSystem Audio;

	HumanView* GetHumanView(){ return (HumanView*)mView; }

protected:
	SDL_Window* mWindow = NULL;
	SDL_Renderer* mRenderer = NULL;

	IGameLogic* mLogic;
	IGameView* mView; //TODO: Should be a vector but simplifying for now

	bool mInitRan = false;

	Language mLanguage;
	std::unordered_map<std::string, std::string> mStringTable;

	EventManager mEventSystem;
	

	// FPS COUNTER
	int mFrameCount;
	float mTimeSinceLastFPSUpdate;
	Text* mFPSText;
};

extern Application* gApp;

#endif