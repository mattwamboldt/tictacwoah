#ifndef INPUT_INTERFACES_H
#define INPUT_INTERFACES_H

#include <SDL/SDL.h>

/*
	These interfaces provide a standard way for input to be passed from devices to
	the game through the application layer. Different areas of the game will have their
	own control objects to translate presses to game commands. This design is from GCC.
	
	TODO: switch from SDL values to strings to make the interface consistent and remove sdl reliance
	TODO: The objects I have using these handlers are creating a lot of redundant code and overrides, to fix
	this we should package all input into a single message and pass that around
*/

class IKeyboardHandler
{
public:
	virtual bool OnKeyPress(SDL_Keycode keycode) = 0;
	virtual bool OnKeyRelease(SDL_Keycode keycode) = 0;
};

class IPointerHandler
{
public:
	virtual bool OnPointerMove(int x, int y) = 0;
	virtual bool OnPointerButtonPress(int x, int y, Uint8 button) = 0;
	virtual bool OnPointerButtonRelease(int x, int y, Uint8 button) = 0;
};

class IGamepadHandler
{
public:
	virtual bool OnButtonPress(Uint8 button) = 0;
	virtual bool OnButtonRelease(Uint8 button) = 0;
};

#endif