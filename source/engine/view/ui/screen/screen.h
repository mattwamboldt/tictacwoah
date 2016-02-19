#ifndef SCREEN_H
#define SCREEN_H

#include "..\core\screenobjectcontainer.h"

// At first the screens are going to be all hard coded, then we'll switch to
// some generic and data driven systems later on as common stuff emerges
class Screen : public ScreenObjectContainer
{
public:
	Screen();
	virtual void Create(){};

	// Transition functions for bringing the screen up and down
	virtual void Display();
	virtual void OnDisplayComplete();

	virtual void Hide();
	virtual void OnHidden();

	virtual bool IsModal(){ return false; }
	bool IsCreated(){ return mCreated; }

protected:
	bool mCreated;
};

#endif