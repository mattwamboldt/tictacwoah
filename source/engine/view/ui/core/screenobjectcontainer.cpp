#include "screenobjectcontainer.h"

ScreenObjectContainer::~ScreenObjectContainer()
{
	for (unsigned int i = 0; i < mChildren.size(); ++i)
	{
		delete mChildren[i];
	}

	mChildren.clear();
	mChildMap.clear();
}

// We render from the start of the vector to the end, and pass input in the opposite direction
// some containers may use a focus system to keep track of a current element and pass info to that element,
// such as a menu or list. that should be the approach we use once basic systems are in place.

void ScreenObjectContainer::Render(int parentX, int parentY)
{
	if (!Visible()) return;

	parentX += mBounds.x;
	parentY += mBounds.y;
	for (unsigned int i = 0; i < mChildren.size(); ++i)
	{
		if (mChildren[i]->Visible())
		{
			mChildren[i]->Render(parentX, parentY);
		}
	}
}

void ScreenObjectContainer::Update()
{
	ScreenObject::Update();

	for (unsigned int i = 0; i < mChildren.size(); ++i)
	{
		mChildren[i]->Update();
	}
}

// by default we pass button input to items that have focus. we'll let child classes determine
// different behaviour or assigning focus
bool ScreenObjectContainer::OnKeyPress(SDL_Keycode keycode)
{
	if (!Enabled()) return false;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnKeyPress(keycode))
		{
			return true;
		}
	}

	return IsModal();
}

bool ScreenObjectContainer::OnKeyRelease(SDL_Keycode keycode)
{
	if (!Enabled()) return false;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnKeyRelease(keycode))
		{
			return true;
		}
	}

	return IsModal();
}

bool ScreenObjectContainer::OnPointerMove(int x, int y)
{
	if (!Enabled()) return false;

	x -= mBounds.x;
	y -= mBounds.y;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnPointerMove(x, y))
		{
			return true;
		}
	}

	return IsModal();
}

bool ScreenObjectContainer::OnPointerButtonPress(int x, int y, Uint8 button)
{
	if (!Enabled()) return false;

	x -= mBounds.x;
	y -= mBounds.y;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnPointerButtonPress(x, y, button))
		{
			return true;
		}
	}

	return IsModal();
}

bool ScreenObjectContainer::OnPointerButtonRelease(int x, int y, Uint8 button)
{
	if (!Enabled()) return false;

	x -= mBounds.x;
	y -= mBounds.y;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnPointerButtonRelease(x, y, button))
		{
			return true;
		}
	}

	return IsModal();
}

bool ScreenObjectContainer::OnButtonPress(Uint8 button)
{
	if (!Enabled()) return false;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnButtonPress(button))
		{
			return true;
		}
	}

	return IsModal();
}

bool ScreenObjectContainer::OnButtonRelease(Uint8 button)
{
	if (!Enabled()) return false;

	for (auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
	{
		if ((*it)->Enabled() && (*it)->OnButtonRelease(button))
		{
			return true;
		}
	}

	return IsModal();
}

ScreenObject* ScreenObjectContainer::operator[](std::string name)
{
	auto child = mChildMap.find(name);
	if (child != mChildMap.end())
	{
		return child->second;
	}

	return NULL;
}

ScreenObject* ScreenObjectContainer::operator[](unsigned int index)
{
	if (index < 0 || index > mChildren.size())
	{
		return NULL;
	}

	return mChildren[index];
}

void ScreenObjectContainer::AddChild(std::string name, ScreenObject* child)
{
	mChildren.push_back(child);
	mChildMap[name] = child;
}
