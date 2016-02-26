#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <vector>

// A game grid is a 2d grid of occupant id's, this means they
// can map to whetever the game wants to store in a grid space
class GameGrid
{
public:
	void Init(int w, int h);
	void Clear();

	int Get(int x, int y) const;
	void Set(int x, int y, int value);

	int Width() const { return mWidth; }
	int Height() const { return mHeight; }

	int Size() const { return mWidth * mHeight; }

	// UNSAFE, make sure to check bounds manually
	int& operator[](int index) { return mOccupants[index]; }
	int operator[](int index) const { return mOccupants[index]; }

	int Count(int occupant) const;

private:
	std::vector<int> mOccupants;

	int mWidth, mHeight;
};

#endif