#ifndef SCREENS_DIFFICULTY_H
#define SCREENS_DIFFICULTY_H

#include <view\ui\screen\screen.h>

// At first the screens are going to be all hard coded, then we'll switch to
// some generic and data driven systems later on as common stuff emerges
class DifficultyPopup : public Screen
{
public:
	virtual void Create();

	virtual bool IsModal() { return true; }

	// Menu callbacks
	void StartEasy();
	void StartMedium();
	void StartHard();
};

#endif
