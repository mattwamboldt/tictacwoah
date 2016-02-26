#include "linescanner.h"
#include "constants.h"

bool Line::operator==(const Line& rval) const
{
	return start == rval.start && length == rval.length && owner == rval.owner && direction == rval.direction;
}

bool Line::Overlaps(const Line& line) const
{
	if (direction == line.direction && owner == line.owner)
	{
		Point projected;
		int projectedLength;
		int baseLength;
		
		// We need the coordinates of the shorter line relative to the longer one
		if (line.length > length)
		{
			projected.x = start.x - line.start.x;
			projected.y = start.y - line.start.y;
			baseLength = line.length;
			projectedLength = length;
			
		}
		else if (line.length < length)
		{
			projected.x = line.start.x - start.x;
			projected.y = line.start.y - start.y;
			baseLength = length;
			projectedLength = line.length;
		}
		else
		{
			return false;
		}

		bool alongAxis = false;
		bool intersect = false;

		if (line.direction == HORIZONTAL)
		{
			alongAxis = projected.y == 0;
			intersect = projected.x + projectedLength >= 0 && projected.x < baseLength;
		}
		else if (line.direction == VERTICAL)
		{
			alongAxis = projected.x == 0;
			intersect = projected.y + projectedLength >= 0 && projected.y < baseLength;
		}
		else if (line.direction == DOWN_RIGHT)
		{
			alongAxis = projected.x == projected.y;
			intersect = projected.x + projectedLength >= 0 && projected.x < baseLength;
		}
		else if (line.direction == DOWN_LEFT)
		{
			alongAxis = projected.x == -projected.y;
			intersect = projected.x - projectedLength <= 0 && abs(projected.x) < baseLength;
		}

		return alongAxis && intersect;
	}

	return false;
}

void LineScanner::Init(GameGrid* grid, LineHandler onLineFound, int directions)
{
	mGrid = grid;
	mLineFound = onLineFound;
	mDirections = directions;
}

void LineScanner::Run()
{
	if (mDirections & HORIZONTAL)
	{
		HorizontalScan();
	}

	if (mDirections & VERTICAL)
	{
		VerticalScan();
	}

	if (mDirections & DOWN_RIGHT)
	{
		DownRightScan();
	}

	if (mDirections & DOWN_LEFT)
	{
		DownLeftScan();
	}
}

void LineScanner::HorizontalScan()
{
	for (int y = 0; y < mGrid->Height(); ++y)
	{
		Scan(0, y, 1, 0, HORIZONTAL);
	}
}

void LineScanner::VerticalScan()
{
	for (int x = 0; x < mGrid->Width(); ++x)
	{
		Scan(x, 0, 0, 1, VERTICAL);
	}
}

void LineScanner::DownRightScan()
{
	// Do the top line
	for (int x = 0; x < mGrid->Width(); ++x)
	{
		Scan(x, 0, 1, 1, DOWN_RIGHT);
	}

	// Then go down the left side
	for (int y = 1; y < mGrid->Height(); ++y)
	{
		Scan(0, y, 1, 1, DOWN_RIGHT);
	}
}

void LineScanner::DownLeftScan()
{
	// Do the top line
	for (int x = 0; x < mGrid->Width(); ++x)
	{
		Scan(x, 0, -1, 1, DOWN_LEFT);
	}

	// Then go down the right side
	for (int y = 1; y < mGrid->Height(); ++y)
	{
		Scan(mGrid->Width() - 1, y, -1, 1, DOWN_LEFT);
	}
}

void LineScanner::Scan(int x, int y, int xRatio, int yRatio, LineDirection direction)
{
	Line current = { 0, Point(x, y), 0, mGrid->Get(x, y), direction };
	int owner = current.owner;

	while (owner != INVALID_POSITION)
	{
		if (owner == current.owner)
		{
			++current.length;
		}
		else
		{
			// We won't bother announcing an empty line
			if (current.owner != NO_ONE)
			{
				mLineFound(mGrid, current);
			}
			
			current.start = { x, y };
			current.owner = owner;
			current.length = 1;
		}

		x += xRatio;
		y += yRatio;
		owner = mGrid->Get(x, y);
	}

	// We won't bother announcing an empty line
	if (current.owner != NO_ONE)
	{
		mLineFound(mGrid, current);
	}
}
