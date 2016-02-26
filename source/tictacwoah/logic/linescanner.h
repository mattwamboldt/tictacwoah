#ifndef LINESCANNER_H
#define LINESCANNER_H

#include <app\core\math\vector.h>
#include <vector>
#include "gamegrid.h"
#include <app\event\fastdelegate.h>

// Line direction is a bitmask enum so we can flag the scaner for which lines to check
// This means we could use it for other grid based puzzles
enum LineDirection
{
	HORIZONTAL = 1,
	VERTICAL = 2,
	DOWN_RIGHT = 4,
	DOWN_LEFT = 8,
	ALL = HORIZONTAL | VERTICAL | DOWN_RIGHT | DOWN_LEFT
};

struct Line
{
	int id;
	Point start;
	int length;
	int owner;
	LineDirection direction;

	bool operator==(const Line& rval) const;
	bool Overlaps(const Line& line) const;
};

typedef fastdelegate::FastDelegate2<GameGrid*, const Line&> LineHandler;

// Looks over the grid and triggers a callback for lines that we find
class LineScanner
{
public:
	// Directions is a bitmask for which directions to check
	void Init(GameGrid* grid, LineHandler onLineFound, int directions);
	void SetGrid(GameGrid* grid) { mGrid = grid; }
	void Run();

private:
	void HorizontalScan();
	void VerticalScan();
	void DownRightScan();
	void DownLeftScan();
	void Scan(int x, int y, int xRatio, int yRatio, LineDirection direction);

	GameGrid* mGrid;
	LineHandler mLineFound;
	int mDirections;
};

#endif
