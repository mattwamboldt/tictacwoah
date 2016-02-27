#include "gamegrid.h"
#include "constants.h"

void GameGrid::Init(int w, int h)
{
	mWidth = w;
	mHeight = h;
	mOccupants.resize(mWidth * mHeight);
	Clear();
}

void GameGrid::Clear()
{
	std::fill(mOccupants.begin(), mOccupants.end(), NO_ONE);
}

int GameGrid::Get(int x, int y) const
{
	if (x >= 0 && y >= 0 && x < mWidth && y < mHeight)
	{
		return mOccupants[x + y * mWidth];
	}

	return INVALID_POSITION;
}

void GameGrid::Set(int x, int y, int value)
{
	if (x >= 0 && y >= 0 && x < mWidth && y < mHeight)
	{
		mOccupants[x + y * mWidth] = value;
	}
}

int GameGrid::Count(int occupant) const
{
	int count = 0;
	for (unsigned int i = 0; i < mOccupants.size(); ++i)
	{
		if (mOccupants[i] == occupant)
		{
			++count;
		}
	}

	return count;
}

Point GameGrid::ToCoordinates(int index) const
{
	return Point(index % mWidth, index / mHeight);
}
