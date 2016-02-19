#include "tictaclogic.h"
#include <app\application.h>
#include "constants.h"

TicTacLogic::TicTacLogic()
{
	mCurrentPlayer = NO_ONE;
	mMode = BASIC;
	mDifficulty = EASY;
	mItemEnabled = false;
	mState = GS_PREGAME;
	mGrid.Init(3, 3);
	mNumOccupied[0] = 0;
}

// This creates the board and does any setup for the game
void TicTacLogic::CreateGame()
{
	// Create a blank board
	if (mMode == BASIC)
	{
		mGrid.Init(3, 3);
	}
	else
	{
		mGrid.Init(9, 9);
		if (mMode == RECURSION)
		{
			mMasterGrid.Init(3, 3);
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		mNumOccupied[i] = 0;
	}

	//TODO: Make this a coin toss
	mCurrentPlayer = PLAYER1;

	mState = GS_RUNNING;
}

void TicTacLogic::Select(int x, int y, int player)
{
	if (mState == GS_RUNNING && IsValidMove(x, y, player))
	{
		// We set the current player for the checks below since in ninja you can jump in at any time
		mCurrentPlayer = player;

		// We need to update the base grid either way
		mGrid.Set(x, y, mCurrentPlayer);

		// Update our counts of occupied and unoccupied to detect draws, (May change draw code later to count player coverage as a tie breaker)
		if (mMode == RECURSION)
		{
			Point masterCoords = { x / 3, y / 3 };

			int subBoard = masterCoords.x + masterCoords.y * 3;
			mNumOccupied[subBoard]++;

			// check a subboard win
			Point subBoardRoot = { masterCoords.x * 3, masterCoords.y * 3 };
			if (HasWon(mGrid, subBoardRoot.x, subBoardRoot.y))
			{
				// Set the master board
				mMasterGrid.Set(masterCoords.x, masterCoords.y, mCurrentPlayer);
				mNumOccupied[9]++;
			}
			else if (mNumOccupied[subBoard] >= 9)
			{
				// How do we break a tie...
				int p1Count = 0;
				int p2Count = 0;
				for (int y = subBoardRoot.y; y < subBoardRoot.y + 3; ++y)
				{
					for (int x = subBoardRoot.x; x < subBoardRoot.x + 3; ++x)
					{
						if (mGrid.Get(x, y) == PLAYER1)
						{
							p1Count++;
						}
						else
						{
							p2Count++;
						}
					}
				}

				// By giving it to the player who has the most territory
				if (p1Count > p2Count)
				{
					mMasterGrid.Set(masterCoords.x, masterCoords.y, PLAYER1);
				}
				else
				{
					mMasterGrid.Set(masterCoords.x, masterCoords.y, PLAYER2);
				}

				mNumOccupied[9]++;
			}

			// Check for the final win/tie
			if (HasWon(mMasterGrid))
			{
				mState = GS_ENDGAME;
				mWinner = mCurrentPlayer;
			}
			else if (mNumOccupied[9] >= mMasterGrid.Size())
			{
				mState = GS_ENDGAME;
				mWinner = NO_ONE;
			}
		}
		// For now all modes are basic until coded
		else
		{
			mNumOccupied[0]++;
			if (HasWon(mGrid))
			{
				mState = GS_ENDGAME;
				mWinner = mCurrentPlayer;
				return;
			}
			else if (mNumOccupied[0] >= mGrid.Size())
			{
				mState = GS_ENDGAME;
				mWinner = NO_ONE;
			}
		}

		// Advance to the next player
		if (mMode != NINJA)
		{
			if (mCurrentPlayer == PLAYER1)
			{
				mCurrentPlayer = PLAYER2;
			}
			else
			{
				mCurrentPlayer = PLAYER1;
			}
		}
	}
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

// I know There are a bunch of double checks here, but This honestly isn't where efficiency matters as much as clarity
bool TicTacLogic::HasWon(const GameGrid& grid, int startX, int startY)
{
	// Hoizontal
	for (int y = startY; y < startY + 3; ++y)
	{
		if (grid.Get(startX, y) == mCurrentPlayer && grid.Get(startX + 1, y) == mCurrentPlayer && grid.Get(startX + 2, y) == mCurrentPlayer)
		{
			return true;
		}
	}

	// Vertical
	for (int x = startX; x < startX + 3; ++x)
	{
		if (grid.Get(x, startY) == mCurrentPlayer && grid.Get(x, startY + 1) == mCurrentPlayer && grid.Get(x, startY + 2) == mCurrentPlayer)
		{
			return true;
		}
	}

	// Diagonal Win Upper Left to Bottom Right
	if (grid.Get(startX, startY) == mCurrentPlayer && grid.Get(startX + 1, startY + 1) == mCurrentPlayer && grid.Get(startX + 2, startY + 2) == mCurrentPlayer)
	{
		return true;
	}

	// Diagonal Win Upper Right to Bottom Left
	if (grid.Get(startX + 2, startY) == mCurrentPlayer && grid.Get(startX + 1, startY + 1) == mCurrentPlayer && grid.Get(startX, startY + 2) == mCurrentPlayer)
	{
		return true;
	}

	return false;
}
