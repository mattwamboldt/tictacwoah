#ifndef SCREENOBJECTCONTAINER_H
#define SCREENOBJECTCONTAINER_H

#include "screenobject.h"
#include <vector>
#include <unordered_map>

// Screen Object Containers have child objects which are passed input, rendered based on ordering and accessible by name
// This basic container will form the hierarchical representation for a screen later down the road
class ScreenObjectContainer : public ScreenObject
{
public:
	// This virtual destructor will clean up all child objects in the container
	// Objects may be newed outside but the screen hierarchy is responsible for cleanup
	virtual ~ScreenObjectContainer();
	
	// We render containers by rendering their children
	virtual void Render(int parentX = 0, int parentY = 0);
	virtual void Update();

	// All input is handled by the container first and children after that
	virtual bool OnKeyPress(SDL_Keycode keycode);
	virtual bool OnKeyRelease(SDL_Keycode keycode);

	virtual bool OnPointerMove(int x, int y);
	virtual bool OnPointerButtonPress(int x, int y, Uint8 button);
	virtual bool OnPointerButtonRelease(int x, int y, Uint8 button);

	virtual bool OnButtonPress(Uint8 button);
	virtual bool OnButtonRelease(Uint8 button);

	// A Modal container absorbs all input, for popups and the like
	virtual bool IsModal() { return false; }

	// Containers have different ways of initializing their children as they are added
	// For instance a plain container can have items anywhere, whereas a scrollable list
	// will maintain a set position for it's children
	virtual int NumChildren(){ return mChildren.size(); };
	virtual ScreenObject* operator[](std::string name);
	virtual ScreenObject* operator[](unsigned int index);
	virtual void AddChild(std::string name, ScreenObject* child);

protected:
	std::vector<ScreenObject*> mChildren;
	std::unordered_map<std::string, ScreenObject*> mChildMap;
};

#endif
