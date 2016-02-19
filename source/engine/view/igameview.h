#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

/*
	A Game View is an interpretation of the game logic, and interacts with it based on that interpretation.
	It takes inputs from the logic, updates its internal view, and outputs commands back. So
	for example a human has a view of the game through their screen and controller, that lets them interact
	with the game logic. A network player would have another view. A journalling system or AI may have yet another
	view. It separates agents acting on the system separate from the system.
*/

#include <SDL/SDL.h>

class IGameView
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual bool HandleInput(const SDL_Event& msg) = 0;
};

#endif