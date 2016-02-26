#include "board.h"
#include <app\application.h>
#include <app\resource\resourcemanager.h>
#include "..\..\logic\constants.h"

Board::Board(TicTacLogic* logic)
{
	mLogic = logic;
	mPlayer1Texture = ResourceManager::Get()->GetTexture("images/xasset.png");
	mPlayer2Texture = ResourceManager::Get()->GetTexture("images/oasset.png");
	mFadeTexture = ResourceManager::Get()->GetTexture("images/fade.png");
}

void Board::Init()
{
	mMasterLine.Visible(false);
	mLines.clear();
	mTileSize = { Width() / mLogic->BoardWidth(), Height() / mLogic->BoardHeight() };

	// We're likley to have uneven bounds so better to adjust this now
	mBounds.w = mTileSize.x * mLogic->BoardWidth();
	mBounds.h = mTileSize.y * mLogic->BoardHeight();

	// Each mode has a different draw color
	switch (mLogic->GetMode())
	{
	case TicTacLogic::BASIC:
		mColor.r = 200;
		mColor.g = 0;
		mColor.b = 200;
		break;

	case TicTacLogic::BIGBOARD:
		mColor.r = 0;
		mColor.g = 200;
		mColor.b = 200;
		break;

	case TicTacLogic::RECURSION:
		mColor.r = 100;
		mColor.g = 200;
		mColor.b = 0;
		break;

	case TicTacLogic::NINJA:
		mColor.r = 200;
		mColor.g = 200;
		mColor.b = 0;
		break;

	default:
		mColor.r = 0;
		mColor.g = 0;
		mColor.b = 0;
		break;
	}
}

void Board::Render(int parentX, int parentY)
{
	SDL_Renderer* screen = gApp->Renderer();
	Point boardPosition = { mBounds.x + parentX, mBounds.y + parentY };

	// This is where each thing gets rendered to
	SDL_Rect destRect = { boardPosition.x, boardPosition.y, mBounds.w, mBounds.h };

	// Draw a backing for the board
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
	SDL_RenderFillRect(screen, &destRect);

	// First we draw the inhabitants
	destRect.w = mTileSize.x;
	destRect.h = mTileSize.y;

	for (int ty = 0; ty < mLogic->BoardHeight(); ++ty)
	{
		for (int tx = 0; tx < mLogic->BoardWidth(); ++tx)
		{
			int occupant = mLogic->Board(tx, ty);

			// Don't draw nothing
			if (occupant == NO_ONE) continue;

			destRect.x = boardPosition.x + mTileSize.x * tx;
			destRect.y = boardPosition.y + mTileSize.y * ty;
			
			// Set the color for the given player, eventually this will be a texture
			if (occupant == PLAYER1)
			{
				SDL_RenderCopy(screen, mPlayer1Texture, NULL, &destRect);
			}
			else if (occupant == PLAYER2)
			{
				SDL_RenderCopy(screen, mPlayer2Texture, NULL, &destRect);
			}
			else
			{
				SDL_SetRenderDrawColor(screen, 0, 200, 0, 255);
				SDL_RenderFillRect(screen, &destRect);
			}
		}
	}	

	// Then the grid lines
	SDL_SetRenderDrawColor(screen, mColor.r, mColor.g, mColor.b, 255);

	for (int ty = 0; ty <= mLogic->BoardHeight(); ++ty)
	{
		int y = boardPosition.y + ty * mTileSize.y;
		SDL_RenderDrawLine(screen, boardPosition.x, y, boardPosition.x + mLogic->BoardWidth() * mTileSize.x, y);
	}

	for (int tx = 0; tx <= mLogic->BoardWidth(); ++tx)
	{
		int x = boardPosition.x + tx * mTileSize.x;
		SDL_RenderDrawLine(screen, x, boardPosition.y, x, boardPosition.y + mLogic->BoardHeight() * mTileSize.y);
	}

	// Then the completed lines
	for (auto iter = mLines.begin(); iter != mLines.end(); ++iter)
	{
		iter->second.Render(boardPosition.x, boardPosition.y);
	}

	// In recursion we want to draw a fader over any completed master grid tiles, and draw those tiles
	if (mLogic->GetMode() == TicTacLogic::RECURSION)
	{
		Point masterTileSize = { mTileSize.x * 3, mTileSize.y * 3 };
		destRect.w = masterTileSize.x;
		destRect.h = masterTileSize.y;

		for (int ty = 0; ty < 3; ++ty)
		{
			for (int tx = 0; tx < 3; ++tx)
			{
				int occupant = mLogic->MasterBoard(tx, ty);

				// Don't draw nothing
				if (occupant == NO_ONE) continue;

				destRect.x = boardPosition.x + masterTileSize.x * tx;
				destRect.y = boardPosition.y + masterTileSize.y * ty;

				SDL_RenderCopy(screen, mFadeTexture, NULL, &destRect);
				if (occupant == PLAYER1)
				{
					SDL_RenderCopy(screen, mPlayer1Texture, NULL, &destRect);
				}
				else
				{
					SDL_RenderCopy(screen, mPlayer2Texture, NULL, &destRect);
				}
			}
		}

		SDL_SetRenderDrawColor(screen, 200, 100, 0, 255);

		// Then the grid lines
		for (int ty = 0; ty <= 3; ++ty)
		{
			int y = boardPosition.y + ty * masterTileSize.y;
			SDL_RenderDrawLine(screen, boardPosition.x, y, boardPosition.x + mLogic->BoardWidth() * mTileSize.x, y);
		}

		for (int tx = 0; tx <= 3; ++tx)
		{
			int x = boardPosition.x + tx * masterTileSize.x;
			SDL_RenderDrawLine(screen, x, boardPosition.y, x, boardPosition.y + mLogic->BoardHeight() * mTileSize.y);
		}

		if (mMasterLine.Visible())
		{
			mMasterLine.Render(boardPosition.x, boardPosition.y);
		}
	}

	// Then the selection rectangle
	bool isMouseOverGrid = mPointerCoords.x >= 0 && mPointerCoords.x < mLogic->BoardWidth() && mPointerCoords.y >= 0 && mPointerCoords.y < mLogic->BoardHeight();
	bool isTileEnabled = true;

	if (mLogic->GetMode() == TicTacLogic::RECURSION)
	{
		int occupant = mLogic->MasterBoard(mPointerCoords.x / 3, mPointerCoords.y / 3);
		if (occupant == PLAYER1 || occupant == PLAYER2)
		{
			isTileEnabled = false;
		}
	}

	if (isMouseOverGrid && isTileEnabled)
	{
		destRect.x = mPointerCoords.x * mTileSize.x + boardPosition.x;
		destRect.y = mPointerCoords.y * mTileSize.y + boardPosition.y;
		destRect.w = mTileSize.x;
		destRect.h = mTileSize.y;
		SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
		SDL_RenderDrawRect(screen, &destRect);
	}
}

void Board::UpdatePointer(int x, int y)
{
	// translate x and y to local space
	x -= X();
	y -= Y();

	// Negatives are special because they get pulled toward 0 giving us entries off the board
	if (x < 0 || y < 0)
	{
		mPointerCoords.x = -1;
		mPointerCoords.y = -1;
	}
	else
	{
		// Scale to the board
		x /= Width() / mLogic->BoardWidth();
		y /= Height() / mLogic->BoardHeight();

		// In future we may need to care about a change in this value for sounds or whatever
		mPointerCoords.x = x;
		mPointerCoords.y = y;
	}
}

bool Board::OnKeyPress(SDL_Keycode keycode)
{
	return false;
}

bool Board::OnKeyRelease(SDL_Keycode keycode)
{
	return false;
}

bool Board::OnPointerMove(int x, int y)
{
	UpdatePointer(x, y);
	return false;
}

bool Board::OnPointerButtonPress(int x, int y, Uint8 button)
{
	UpdatePointer(x, y);
	mLogic->Select(mPointerCoords.x, mPointerCoords.y, mLogic->CurrentPlayer());
	return false;
}

bool Board::OnPointerButtonRelease(int x, int y, Uint8 button)
{
	UpdatePointer(x, y);
	return false;
}

bool Board::OnButtonPress(Uint8 button)
{
	return false;
}

bool Board::OnButtonRelease(Uint8 button)
{
	return false;
}

void Board::AddLine(const Line& line, bool masterGrid)
{
	if (masterGrid)
	{
		mMasterLine = ScreenLine(line, Point(mTileSize.x * 3, mTileSize.y * 3));
		mMasterLine.Visible(true);
	}
	else
	{
		mLines[line.id] = ScreenLine(line, mTileSize);
	}
}

void Board::ChangeLine(const Line& line)
{
	mLines[line.id].Change(line);
}

void Board::RemoveLine(int lineId)
{
	mLines.erase(lineId);
}