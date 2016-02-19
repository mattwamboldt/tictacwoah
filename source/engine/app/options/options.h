#ifndef OPTIONS
#define OPTIONS

// TODO: Create a storage mechanism for game settings that can be loaded from a file

const int screenWidth = 800;
const int screenHeight = 600;

#include <app\core\math\vector.h>
#include <app\parsers\xml\tinyxml2.h>
#include <app\util\macros.h>

struct GameOptions
{
	// Rendering options
	bool RunFullSpeed;
	bool FullScreen;
	Point ScreenSize;

	// Sound options
	float SFXVolume;
	float MusicVolume;

	bool UseDevDirectory;

	// The doc may have further options
	// TODO: Switch this whole system to a name value pair situation to have completely flexible options
	tinyxml2::XMLDocument Doc;

	GameOptions();

	void Init(const char* xmlFilePath);
};

#endif