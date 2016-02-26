#ifndef SCREENLINE_H
#define SCREENLINE_H

#include <view\ui\core\screenobject.h>
#include "../../logic/linescanner.h"

class ScreenLine : public ScreenObject
{
public:
	ScreenLine() {}
	ScreenLine(const Line& line, Point tileSize);
	void Change(const Line& line);

	virtual void Render(int parentX = 0, int parentY = 0);

private:
	Point mTileSize;
};

#endif