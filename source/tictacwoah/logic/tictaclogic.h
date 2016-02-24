#ifndef TICTACLOGIC_H
#define TICTACLOGIC_H

#include "gamegrid.h"
#include "constants.h"

// Holds game state and contains logic to create and run the game
// Several of these functions are from an earlier event based tic tac toe game
class TicTacLogic
{
public:
	enum Mode
	{
		BASIC = 0,
		BIGBOARD,
		NINJA,
		RECURSION,
		NUM_GAMEMODES
	};

	enum Difficulty
	{
		EASY = 0,
		MEDIUM,
		HARD,
		NUM_DIFFICULTIES
	};

	enum GameState
	{
		GS_PREGAME = 0,
		GS_RUNNING,
		GS_PAUSED,
		GS_ENDGAME,
		NUM_GAMESTATES
	};

	TicTacLogic();

	// This creates the board and does any setup for the game
	void CreateGame();
	void Select(int x, int y, int player);
	void TogglePause();

	void EndGame(int winner = NO_ONE);

	bool IsValidMove(int x, int y, int player);

	// Getters/Setters
	void SetMode(Mode mode);
	Mode GetMode(){ return mMode; }

	void SetDifficulty(Difficulty difficulty);
	Difficulty GetDifficulty(){ return mDifficulty; }

	void SetItemsEnabled(bool enabled);
	bool GetItemsEnabled(){ return mItemEnabled; }

	int Board(int x, int y){ return mGrid.Get(x, y); }
	int MasterBoard(int x, int y){ return mMasterGrid.Get(x, y); }

	int BoardWidth() { return mGrid.Width(); }
	int BoardHeight() { return mGrid.Height(); }

	int CurrentPlayer(){ return mCurrentPlayer; }
	int GetWinner(){ return mWinner; }

private:
	bool HasWon(const GameGrid& grid, int startX = 0, int startY = 0);

	Mode mMode;
	Difficulty mDifficulty;
	GameState mState;
	int mWinner;
	GameGrid mGrid;

	// Doesn't matter in Ninja mode
	int mCurrentPlayer;
	
	// Available in the modes that support them
	bool mItemEnabled;

	// Used to tell if a board is full, ie tied, we have 10 to track the sub boards in recursion mode
	int mNumOccupied[10];

	// Used in Recursive mode to track overall progress
	GameGrid mMasterGrid;
};

#endif
