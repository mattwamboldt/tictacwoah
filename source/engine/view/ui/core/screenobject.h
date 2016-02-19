#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include <app\core\math\vector.h>
#include <view\render\color.h>
#include <app\input\inputinterfaces.h>
#include <app\event\fastdelegate.h>
#include <string>

typedef fastdelegate::FastDelegate0<> AnimationCompleteHandler;

// A fresh attempt at UI. Think of ui elements as objects on a screen that can be moved around and manipulated
class ScreenObject : public IKeyboardHandler, public IPointerHandler, public IGamepadHandler
{
public:
	// Creates the object with some reasonable defaults
	ScreenObject();

	// Since these objects are manipulated generically the destructor should be virtual
	virtual ~ScreenObject() {}

	// ---------------
	// RENDERING
	// ---------------

	// If an object is on the screen it's needs to be shown to the viewer
	// To handle hierarchy we'll evetually want a screen matrix stack, or something
	// along those lines, but for basic layout this'll do
	virtual void Render(int parentX = 0, int parentY = 0);

	// If we're rendering we need to be able to set the objects visibility
	bool Visible();
	void Visible(bool visible);

	// Control where the object is relative to it's parent
	void X(int x);
	int X();
	void Y(int y);
	int Y();
	void Position(int x, int y);
	Point Position();

	// Control how big it is 
	virtual void Width(int width);
	int Width();
	virtual void Height(int height);
	int Height();
	virtual void Dimensions(int width, int height);
	Point Dimensions();

	// What Color it is
	virtual void SetColor(Color color);
	Color GetColor();

	// --------------
	// INPUT
	// A screen object can handle all forms of input, by default they do nothing unless overridden
	// --------------
	virtual bool OnKeyPress(SDL_Keycode keycode) { return false; }
	virtual bool OnKeyRelease(SDL_Keycode keycode) { return false; }
	
	virtual bool OnPointerMove(int x, int y) { return false; }
	virtual bool OnPointerButtonPress(int x, int y, Uint8 button) { return false; }
	virtual bool OnPointerButtonRelease(int x, int y, Uint8 button) { return false; }

	virtual bool OnButtonPress(Uint8 button) { return false; }
	virtual bool OnButtonRelease(Uint8 button) { return false; }

	// Focus management is key for making sure the right object gets the right
	virtual bool HasFocus(){ return mHasFocus; }
	virtual void SetFocus(bool focus){ mHasFocus = focus; }
	virtual int GetFocusOrder(){ return mFocusOrder; }
	virtual void SetFocusOrder(int order){ mFocusOrder = order; }

	// Enabled determines if an object recieves input, it may also effect rendering on some control types
	bool Enabled();
	void Enabled(bool enabled);

	// --------------
	// HIERARCHY
	// By default a screen object has no children, but derivative classes will act as containers
	// And those will have children. To keep the interfaces the same the functions exist in the base class
	// --------------
	virtual int NumChildren(){ return 0; }
	virtual ScreenObject* operator[](std::string name){ return NULL; }
	virtual ScreenObject* operator[](unsigned int index){ return NULL; }
	virtual void AddChild(std::string name, ScreenObject* child) {}

	// TODO: at some point zorder will matter, that should go here

	// -------------
	// ANIMATION
	// -------------
	// TODO: For now we'll embed animation directly in the screen object and hardcode transitions
	// Eventually we'll key frame it, which means we store the animation frames as start and end pairs, with an update function and duration
	virtual void Update();
	void Move(int x, int y, Uint32 ms);
	void Move(int x, int y, Uint32 ms, AnimationCompleteHandler onComplete);

protected:
	// TODO: Replace SDL types cause they're getting annoying
	SDL_Rect mBounds;
	bool mVisible;
	bool mEnabled;
	Color mColor;
	bool mHasFocus;
	int mFocusOrder;

	// Animation variables
	bool mAnimating;
	Point mStartLocation;
	Point mDestLocation;
	Uint32 mStartTicks;
	Uint32 mEndTicks;
	AnimationCompleteHandler mAnimHandler;
};

#endif