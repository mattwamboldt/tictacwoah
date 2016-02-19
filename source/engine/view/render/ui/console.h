#ifndef CONSOLE_H
#define CONSOLE_H
#include <view\render\ui\textbox.h>
#include <view\render\2d\displayobject.h>
#include <string>
using namespace std;

class IConsoleHandler
{
public:
	virtual void InputEntered(string text) = 0;
};

class Console : public DisplayObject
{
public:
	Console(IConsoleHandler* callbackObj) : handler(callbackObj) {};
	void Init(TTF_Font* font, int width, int height, int x, int y);

	virtual void Render();
	void HandleInput(SDL_KeyboardEvent key, bool isPress);
	void HandleText(SDL_TextInputEvent textEvent);

	// Can use this for debug text, adds text to the output without triggering the callback
	void WriteLine(string text);

	bool enabled;
private:
	string inputString;
	string outputString;
	int width;
	int height;
	TextBox output;
	TextBox input;
	DisplayObject backing;
	IConsoleHandler* handler;
};

#endif