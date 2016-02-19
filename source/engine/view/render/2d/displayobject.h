#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include "SDL/SDL.h"

/*
The 2d rendering system uses a similar structure to flash, and really many systems,
the names adobe picked just make the most logical sense, but a bunch will
be different execution wise

The root of the hierarchy has a display object, which is a thing that can be rendered on the screen
Below that we have containers which can hold other display objects and create a new local coordinate
system that their children are relative to, and below that we have animatable objects, which basically
have frames which are other sets of display objects that are tweened using some easing formula

By creating a way to grab children using a hierarchical representation and exposing parameters to script
We can separate the view from the controller
*/

class DisplayObject
{
public:
	DisplayObject() : x(0), y(0), width(100), height(100), visible(true){ color.a = color.r = color.g = color.b = 255; }

	// Position
	int x;
	int y;

	// Bounds
	int width;
	int height;

	bool visible;

	SDL_Color color;

	virtual void Render();
};

#endif