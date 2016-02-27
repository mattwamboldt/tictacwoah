#include "tictaclogic.h"
#include <app\application.h>
#include "constants.h"
#include <app/event/eventmanager.h>
#include "../events/gameevents.h"

int TicTacLogic::NextAvailableID = 1;

TicTacLogic::TicTacLogic()
{
	mCurrentPlayer = NO_ONE;
	mMode = BASIC;
	mDifficulty = EASY;
	mItemEnabled = false;
	mState = GS_PREGAME;
	mGrid.Init(3, 3);
}

// This creates the board and does any setup for the game
void TicTacLogic::CreateGame()
{
	// Create a blank board
	if (mMode == BASIC)
	{
		mGrid.Init(3, 3);
		mScanner.Init(&mGrid, fastdelegate::MakeDelegate(this, &TicTacLogic::OnLineFoundBasic), ALL);
	}
	else
	{
		if (mMode == RECURSION)
		{
			mGrid.Init(9, 9);
			mMasterGrid.Init(3, 3);
			mScanner.Init(&mMasterGrid, fastdelegate::MakeDelegate(this, &TicTacLogic::OnLineFoundBasic), ALL);
			for (int i = 0; i < 9; ++i)
			{
				mSubGrids[i].Init(3, 3);
			}
		}
		else
		{
			mGrid.Init(9, 9);
			mScanner.Init(&mGrid, fastdelegate::MakeDelegate(this, &TicTacLogic::OnLineFound), ALL);
			mPlayer1Score = 0;
			mPlayer2Score = 0;
			mLines.clear();
		}
	}

	//TODO: Make this a coin toss
	mCurrentPlayer = PLAYER1;

	mState = GS_RUNNING;

	EventManager::Get()->Queue(new CreateGameEvent());
}

bool TicTacLogic::IsDraw(const GameGrid& grid) const
{
	return mState == GS_RUNNING && grid.Count(PLAYER1) + grid.Count(PLAYER2) >= grid.Size();
}

bool TicTacLogic::Select(int x, int y, int player)
{
	if (mState != GS_RUNNING || !IsValidMove(x, y, player)) return false;

	// We set the current player for the checks below since in ninja you can jump in at any time
	mCurrentPlayer = player;

	// We need to update the base grid either way
	mGrid.Set(x, y, mCurrentPlayer);

	// Update our counts of occupied and unoccupied to detect draws, (May change draw code later to count player coverage as a tie breaker)
	if (mMode == RECURSION)
	{
		Point masterCoords = { x / 3, y / 3 };

		int subBoard = masterCoords.x + masterCoords.y * 3;
		GameGrid& subGrid = mSubGrids[subBoard];

		// We only update the subboards for the ai for now
		subGrid.Set(x - masterCoords.x * 3, y - masterCoords.y * 3, mCurrentPlayer);

		// check a subboard win
		Point subBoardRoot = { masterCoords.x * 3, masterCoords.y * 3 };
		if (HasWon(mGrid, subBoardRoot.x, subBoardRoot.y))
		{
			// Set the master board
			mMasterGrid.Set(masterCoords.x, masterCoords.y, mCurrentPlayer);
		}
		else if (IsDraw(subGrid))
		{
			// How do we break a tie...
			// By giving it to the player who has the most territory
			if (subGrid.Count(PLAYER1) > subGrid.Count(PLAYER2))
			{
				mMasterGrid.Set(masterCoords.x, masterCoords.y, PLAYER1);
			}
			else
			{
				mMasterGrid.Set(masterCoords.x, masterCoords.y, PLAYER2);
			}
		}
	}

	mScanner.Run();

	if (mMode == RECURSION)
	{
		if (IsDraw(mMasterGrid))
		{
			EndGame();
		}
	}
	else if (IsDraw(mGrid))
	{
		int winner = NO_ONE;

		if (mMode != BASIC)
		{
			if (mPlayer1Score > mPlayer2Score)
			{
				winner = PLAYER1;
			}
			else if (mPlayer1Score < mPlayer2Score)
			{
				winner = PLAYER2;
			}
		}

		EndGame(winner);
	}

	// Advance to the next player
	if (mMode != NINJA)
	{
		if (mCurrentPlayer == PLAYER1)
		{
			mCurrentPlayer = PLAYER2;
			RunAI();
		}
		else
		{
			mCurrentPlayer = PLAYER1;
		}
	}

	return true;
}

void TicTacLogic::EndGame(int winner)
{
	mState = GS_ENDGAME;
	mWinner = winner;
	EventManager::Get()->Queue(new MatchCompleteEvent(mWinner));
}

bool TicTacLogic::IsValidMove(int x, int y, int player)
{
	// It's a bit easier to understand these checks as separate lines
	// It's not efficient but again logic is not the place where that matters typically
	
	// Make sure it's the right player in the turn based modes
	if (mMode != NINJA && mCurrentPlayer != player) return false;

	// Make sure the square is selectable
	int occupant = mGrid.Get(x, y);
	if (occupant == INVALID_POSITION || occupant == PLAYER1 || occupant == PLAYER2) return false;

	// In recursion we also need to prevent clicking on completed sections of the board once a winner is picked
	if (mMode == RECURSION && mMasterGrid.Get(x/3, y/3) != NO_ONE) return false;
	
	// ALL GO!
	return true;
}

void TicTacLogic::TogglePause()
{
	if (mState == GS_RUNNING)
	{
		mState = GS_PAUSED;
	}
	else if (mState == GS_PAUSED)
	{
		mState = GS_RUNNING;
	}
}

// Getters/Setters
void TicTacLogic::SetMode(Mode mode)
{
	mMode = mode;
}

void TicTacLogic::SetDifficulty(Difficulty difficulty)
{
	mDifficulty = difficulty;
}

void TicTacLogic::SetItemsEnabled(bool enabled)
{
	mItemEnabled = enabled;
}

int TicTacLogic::GetScore(int playerId)
{
	if (playerId == PLAYER1) return mPlayer1Score;
	if (playerId == PLAYER2) return mPlayer2Score;
	return 0;
}

// I know There are a bunch of double checks here, but This honestly isn't where efficiency matters as much as clarity
bool TicTacLogic::HasWon(const GameGrid& grid, int startX, int startY)
{
	Line win;
	win.length = 3;
	win.owner = mCurrentPlayer;

	// Hoizontal
	for (int y = startY; y < startY + 3; ++y)
	{
		if (grid.Get(startX, y) == mCurrentPlayer && grid.Get(startX + 1, y) == mCurrentPlayer && grid.Get(startX + 2, y) == mCurrentPlayer)
		{
			win.direction = HORIZONTAL;
			win.start.x = startX;
			win.start.y = y;
			AddLine(&grid, win);
			return true;
		}
	}

	// Vertical
	for (int x = startX; x < startX + 3; ++x)
	{
		if (grid.Get(x, startY) == mCurrentPlayer && grid.Get(x, startY + 1) == mCurrentPlayer && grid.Get(x, startY + 2) == mCurrentPlayer)
		{
			win.direction = VERTICAL;
			win.start.x = x;
			win.start.y = startY;
			AddLine(&grid, win);
			return true;
		}
	}

	// Diagonal Win Upper Left to Bottom Right
	if (grid.Get(startX, startY) == mCurrentPlayer && grid.Get(startX + 1, startY + 1) == mCurrentPlayer && grid.Get(startX + 2, startY + 2) == mCurrentPlayer)
	{
		win.direction = DOWN_RIGHT;
		win.start.x = startX;
		win.start.y = startY;
		AddLine(&grid, win);
		return true;
	}

	// Diagonal Win Upper Right to Bottom Left
	if (grid.Get(startX + 2, startY) == mCurrentPlayer && grid.Get(startX + 1, startY + 1) == mCurrentPlayer && grid.Get(startX, startY + 2) == mCurrentPlayer)
	{
		win.direction = DOWN_LEFT;
		win.start.x = startX + 2;
		win.start.y = startY;
		AddLine(&grid, win);
		return true;
	}

	return false;
}

void TicTacLogic::OnLineFoundBasic(GameGrid* grid, const Line& line)
{
	if (line.length >= 3)
	{
		EventManager::Get()->Queue(new LineEvent(line, OBJECT_CREATED, mMode == RECURSION ? 1 : 0));
		EndGame(line.owner);
	}
}

void TicTacLogic::OnLineFound(GameGrid* grid, const Line& line)
{
	if (line.length >= 3)
	{
		std::vector<int> overlappingLines;

		// Find out if this is extending an existing line, is a new one, or is merging multiple
		// We need to do this before deleting any lines, because the count effects
		// how we handle things
		for (std::vector<Line>::iterator iter = mLines.begin(); iter != mLines.end(); ++iter)
		{
			const Line& currentLine = *iter;
			if (currentLine == line)
			{
				return;
			}
			else if (line.Overlaps(currentLine))
			{
				overlappingLines.push_back(currentLine.id);
			}
		}

		// If it doesn't overlap existing lines than it's a new line
		if (overlappingLines.size() == 0)
		{
			AddLine(grid, line);
		}
		// If it just overlaps one than we're extending an existing line
		else if (overlappingLines.size() == 1)
		{
			// I know this is inefficient but trying to get stuff done
			for (unsigned int i = 0; i < mLines.size(); ++i)
			{
				if (mLines[i].id == overlappingLines[0])
				{
					Line& existingLine = mLines[i];
					ScoreHandleLineExtended(existingLine, line);

					existingLine.start = line.start;
					existingLine.length = line.length;
					EventManager::Get()->Queue(new LineEvent(existingLine, OBJECT_MODIFIED));
					break;
				}
			}
		}
		// Otherwise we're merging lines
		else
		{
			// Again, stupid inefficient, but we never have that many to deal with anyway
			for (unsigned int i = 0; i < overlappingLines.size(); ++i)
			{
				for (auto iter = mLines.begin(); iter != mLines.end(); ++iter)
				{
					if ((*iter).id == overlappingLines[i])
					{
						mLines.erase(iter);
						break;
					}
				}
			}

			mLines.push_back(line);
			Line& newLine = mLines[mLines.size() - 1];
			newLine.id = NextAvailableID;
			++NextAvailableID;
			ScoreHandleLineMerge(line);
			EventManager::Get()->Queue(new LineMergeEvent(newLine, overlappingLines));
		}
	}
}

void TicTacLogic::AddLine(const GameGrid* grid, const Line& line)
{
	mLines.push_back(line);
	Line& newline = mLines[mLines.size() - 1];
	newline.id = NextAvailableID;
	++NextAvailableID;
	ScoreHandleLineMade(newline);
	int id = 0;
	if (grid == &mMasterGrid) id = 1;
	EventManager::Get()->Queue(new LineEvent(newline, OBJECT_CREATED, id));
}

void TicTacLogic::IncreaseScore(int player, int amount)
{
	if (player == PLAYER1)
	{
		mPlayer1Score += amount;
		EventManager::Get()->Queue(new ScoreChangeEvent(PLAYER1, mPlayer1Score));
	}
	else
	{
		mPlayer2Score += amount;
		EventManager::Get()->Queue(new ScoreChangeEvent(PLAYER2, mPlayer2Score));
	}
}

void TicTacLogic::ScoreHandleLineMade(const Line& line)
{
	IncreaseScore(line.owner, 30);
}

void TicTacLogic::ScoreHandleLineExtended(const Line& oldline, const Line& newline)
{
	IncreaseScore(newline.owner, (newline.length - oldline.length) * 20);
}

void TicTacLogic::ScoreHandleLineMerge(const Line& line)
{
	IncreaseScore(line.owner, line.length * 50);
}

int TicTacLogic::RandomFree(const GameGrid& grid)
{
	int randomIndex = rand() % grid.Size();
	int functionalIndex = 0;
	while (randomIndex > 0 || grid[functionalIndex] != NO_ONE)
	{
		if (grid[functionalIndex] == NO_ONE)
		{
			--randomIndex;
		}

		functionalIndex = (functionalIndex + 1) % grid.Size();
	}

	return functionalIndex;
}

bool TicTacLogic::BlockOpponent(Point& move)
{
	return false;
}

bool TicTacLogic::MakeLine(Point& move)
{
	return false;
}

void TicTacLogic::RandomMove(Point& move)
{
	if (mMode == RECURSION)
	{
		int masterIndex = RandomFree(mMasterGrid);
		int subIndex = RandomFree(mSubGrids[masterIndex]);
		move.x = (masterIndex % 3) * 3 + (subIndex % 3);
		move.y = (masterIndex / 3) * 3 + (subIndex / 3);
	}
	else
	{
		int randomIndex = RandomFree(mGrid);
		move.x = randomIndex % mGrid.Width();
		move.y = randomIndex / mGrid.Width();
	}
}

void TicTacLogic::RunAI()
{
	if (mState != GS_RUNNING) return;

	Point move;

	// At a base level, we always make a random move
	RandomMove(move);

	Select(move.x, move.y, PLAYER2);
}
