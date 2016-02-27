#ifndef TICTACLOGIC_H
#define TICTACLOGIC_H

#include "gamegrid.h"
#include "constants.h"
#include "linescanner.h"

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
	bool Select(int x, int y, int player);
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

	void OnLineFound(GameGrid* grid, const Line& line);
	void OnLineFoundBasic(GameGrid* grid, const Line& line);

	int GetScore(int playerId);

	void RunAI();

private:
	bool HasWon(const GameGrid& grid, int startX = 0, int startY = 0);

	// Scoring system functions for ninja mode
	void ScoreHandleLineMade(const Line& line);
	void ScoreHandleLineExtended(const Line& oldline, const Line& newline);
	void ScoreHandleLineMerge(const Line& line);

	void IncreaseScore(int player, int amount);
	void AddLine(const GameGrid* grid, const Line& line);

	bool IsDraw(const GameGrid& grid) const;

	Mode mMode;
	Difficulty mDifficulty;
	GameState mState;
	int mWinner;
	GameGrid mGrid;

	// Doesn't matter in Ninja mode
	int mCurrentPlayer;
	
	// Available in the modes that support them
	bool mItemEnabled;

	// Used in Recursive Mode
	GameGrid mSubGrids[9];
	GameGrid mMasterGrid;

	LineScanner mScanner;
	int mPlayer1Score;
	int mPlayer2Score;
	std::vector<Line> mLines;

	static int NextAvailableID;

	// ============
	// AI Functions
	// TODO: I know this should be separated, lesson learned for next time to architect a bit better
	bool MakeLine(Point& move);
	void RandomMove(Point& move);

	int RandomFree(const GameGrid& grid);
};

#endif
