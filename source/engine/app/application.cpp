#include "application.h"
#include "audio/audio.h"
#include "resource\resourcemanager.h"

#include "SDL/SDL_image.h"
#include <cstdio>
#include "SDL/SDL_ttf.h"
#include <app\debug\logging.h>
#include <app\parsers\xml\tinyxml2.h>

Application* gApp = NULL;

Application::Application()
	: mEventSystem("main", true), mFPSText(NULL)
{
	mLanguage = INVALID_LANG;
	gApp = this;
	mInitRan = false;
}

bool Application::Init()
{
	Options.Init("options.xml");

	//Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Debug::console("SDL_Init: %s\n", SDL_GetError());
		return false;
	}

	ResourceManager::Create();

	if (!SetLanguage(DEFAULT_LANG))
	{
		Debug::console("Failed to load default string table.\n");
		return false;
	}

	mInitRan = true;

	// load support for the PNG image formats
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		Debug::console("IMG_Init: Failed to init required png support!\n");
		Debug::console("IMG_Init: %s\n", IMG_GetError());
		return false;
	}

	flags = 0;
	if (Options.FullScreen) flags |= SDL_WINDOW_FULLSCREEN;

	mWindow = SDL_CreateWindow(Name(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Options.ScreenSize.x, Options.ScreenSize.y, flags);
	if (mWindow == NULL)
	{
		Debug::console("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	if (mRenderer == NULL)
	{
		Debug::console("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_RenderSetLogicalSize(mRenderer, Options.ScreenSize.x, Options.ScreenSize.y);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	SDL_AudioSpec wanted;
	wanted.freq = FREQUENCY;
	wanted.format = AUDIO_S8;
	wanted.channels = 1;    /* 1 = mono, 2 = stereo */
	wanted.samples = SAMPLE_RATE;  /* Good low-latency value for callback */
	wanted.callback = audioCallback;
	wanted.userdata = NULL;

	/* Open the audio device, forcing the desired format */
	if (SDL_OpenAudio(&wanted, NULL) < 0)
	{
		Debug::console("Couldn't open audio: %s\n", SDL_GetError());
		return false;
	}

	InitAudio();
	SDL_PauseAudio(0);
	TTF_Init();

	// create the fps counter
	mFPSText = new Text("fps 0", "fonts/VeraMono.ttf", 20);
	mFrameCount = 0;
	mTimeSinceLastFPSUpdate = 0.0f;

	return CreateLogicAndViews();
}

void Application::Run()
{
	bool quit = false;
	SDL_Event event;

	Uint32 old_time, current_time;
	float ftime;
	current_time = SDL_GetTicks();

	while (!quit)
	{
		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime = (current_time - old_time) / 1000.0f;

		// Respond to user OS and input events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYUP:
				case SDL_KEYDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEMOTION:
				case SDL_CONTROLLERBUTTONUP:
				case SDL_CONTROLLERBUTTONDOWN:
					mView->HandleInput(event);
					break;
			}
		}

		// Give it 20 ms
		if (!mEventSystem.Update(20))
		{
			Debug::console("EVENT SYSTEM OVERLOADED");
		}

		mView->Update(ftime);

		// TODO: Not all aplications will have a rednerer so we should remove this dependency in the base class, shoudl probably be a human view thing?
		// Update the frame counter
		mTimeSinceLastFPSUpdate += ftime;
		if (mTimeSinceLastFPSUpdate > 1.0f)
		{
			if (mFPSText) mFPSText->SetText(("fps:  " + std::to_string(mFrameCount)).c_str());
			mFrameCount = 0;
			mTimeSinceLastFPSUpdate = 0.0f;
		}

		++mFrameCount;

		//Redraw
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		//draw the game
		mView->Render();

		// Draw the fps counter
		if (mFPSText) mFPSText->Render();

		//push the screen to the video card and display
		SDL_RenderPresent(mRenderer);

		// So that we play nice with the OS wait a ms. If we ever want to cap framerate we would do it here
		SDL_Delay(1);
	}
}

void Application::Shutdown()
{
	if (mInitRan)
	{
		ResourceManager::Destroy();

		if (TTF_WasInit())
		{
			TTF_Quit();
		}

		IMG_Quit();
		DestroyAudio();
		SDL_CloseAudio();
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
	}
}

const char* Application::GetText(std::string id)
{
	auto localizedString = mStringTable.find(id);
	if (localizedString == mStringTable.end())
	{
		Debug::console("String %s not found!", id.c_str());
		return id.c_str();
	}

	return localizedString->second.c_str();
}

const char* gLanguageCodes[NUM_LANGUAGES] = {
	"english"
};

bool Application::SetLanguage(Language language)
{
	if (language != mLanguage)
	{
		std::string languageFile = "strings/";
		languageFile += gLanguageCodes[language];
		languageFile += ".xml";

		// TODO: this shoudl be loaded from the cache to avoid this problem
		if (gApp->Options.UseDevDirectory)
		{
			languageFile = "../data/" + languageFile;
		}

		tinyxml2::XMLDocument doc;
		doc.LoadFile(languageFile.c_str());

		tinyxml2::XMLElement* pRoot = doc.RootElement();
		if (!pRoot)
		{
			Debug::console("Failed to load loc database %s.\n", languageFile.c_str());
			return false;
		}

		mLanguage = language;
		mStringTable.clear();

		//TODO: Issue warnings for duplicates and empty ids
		for (tinyxml2::XMLElement* pElem = pRoot->FirstChildElement(); pElem; pElem = pElem->NextSiblingElement())
		{
			const char* id = pElem->Attribute("id");
			const char* text = pElem->Attribute("value");
			if (id && text)
			{
				//TODO: Issue warnings for any duplicates
				mStringTable[id] = text;
			}
		}
	}

	return true;
}
