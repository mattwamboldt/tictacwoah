#include "options.h"
#include <string>

// Set some reasonable defaults
GameOptions::GameOptions()
{
	RunFullSpeed = false;
	FullScreen = true;
	ScreenSize = Point(1024, 768);
	SFXVolume = 1.0f;
	MusicVolume = 1.0f;
	UseDevDirectory = false;
}

void GameOptions::Init(const char* xmlFilePath)
{
	// Overwrite settings with the xml given file
	if (Doc.LoadFile(xmlFilePath) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *pRoot = Doc.RootElement();
		if (!pRoot)
			return;

		// Loop through each child element and load the component
		tinyxml2::XMLElement* pNode = NULL;
		pNode = pRoot->FirstChildElement("graphics");
		if (pNode)
		{
			std::string attribute;

			if (pNode->Attribute("width"))
			{
				ScreenSize.x = pNode->IntAttribute("width");
				if (ScreenSize.x < 800) ScreenSize.x = 800;
			}

			if (pNode->Attribute("height"))
			{
				ScreenSize.y = pNode->IntAttribute("height");
				if (ScreenSize.y < 600) ScreenSize.y = 600;
			}

			if (pNode->Attribute("runfullspeed"))
			{
				RunFullSpeed = pNode->BoolAttribute("runfullspeed");
			}

			if (pNode->Attribute("fullscreen"))
			{
				FullScreen = pNode->BoolAttribute("fullscreen");
			}
		}

		pNode = pRoot->FirstChildElement("resources");
		if (pNode)
		{
			if (pNode->Attribute("usedevdirectory"))
			{
				UseDevDirectory = pNode->BoolAttribute("usedevdirectory");
			}
		}

		pNode = pRoot->FirstChildElement("sound");
		if (pNode)
		{
			MusicVolume = pNode->IntAttribute("musicvolume") / 100.0f;
			SFXVolume = pNode->IntAttribute("sfxvolume") / 100.0f;
		}
	}
}
