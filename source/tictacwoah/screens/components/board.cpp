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

void Board::Render(int parentX, int parentY)
{
	SDL_Renderer* screen = gApp->Renderer();
	Point boardPosition = { mBounds.x + parentX, mBounds.y + parentY };
	Point tileSize = { Width() / mLogic->BoardWidth(), Height() / mLogic->BoardHeight() };

	// We're likley to have uneven bounds so better to adjust this now
	mBounds.w = tileSize.x * mLogic->BoardWidth();
	mBounds.h = tileSize.y * mLogic->BoardHeight();

	// This is where each thing gets rendered to
	SDL_Rect destRect = { boardPosition.x, boardPosition.y, mBounds.w, mBounds.h };

	// Draw a backing for the board
	SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
	SDL_RenderFillRect(screen, &destRect);

	// First we draw the inhabitants
	destRect.w = tileSize.x;
	destRect.h = tileSize.y;

	for (int ty = 0; ty < mLogic->BoardHeight(); ++ty)
	{
		for (int tx = 0; tx < mLogic->BoardWidth(); ++tx)
		{
			int occupant = mLogic->Board(tx, ty);

			// Don't draw nothing
			if (occupant == NO_ONE) continue;

			destRect.x = boardPosition.x + tileSize.x * tx;
			destRect.y = boardPosition.y + tileSize.y * ty;
			
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

	// Each mode has a different draw color, we'll move this to a one time place later, but for now
	switch (mLogic->GetMode())
	{
	case TicTacLogic::BASIC:
		SDL_SetRenderDrawColor(screen, 200, 0, 200, 255);
		break;

	case TicTacLogic::BIGBOARD:
		SDL_SetRenderDrawColor(screen, 0, 200, 200, 255);
		break;

	case TicTacLogic::RECURSION:
		SDL_SetRenderDrawColor(screen, 100, 200, 0, 255);
		break;

	case TicTacLogic::NINJA:
		SDL_SetRenderDrawColor(screen, 200, 200, 0, 255);
		break;

	default:
		SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
		break;
	}

	// Then the grid lines
	for (int ty = 0; ty <= mLogic->BoardHeight(); ++ty)
	{
		int y = boardPosition.y + ty * tileSize.y;
		SDL_RenderDrawLine(screen, boardPosition.x, y, boardPosition.x + mLogic->BoardWidth() * tileSize.x, y);
	}

	for (int tx = 0; tx <= mLogic->BoardWidth(); ++tx)
	{
		int x = boardPosition.x + tx * tileSize.x;
		SDL_RenderDrawLine(screen, x, boardPosition.y, x, boardPosition.y + mLogic->BoardHeight() * tileSize.y);
	}

	// In recursion we want to draw a fader over any completed master grid tiles, and draw those tiles
	if (mLogic->GetMode() == TicTacLogic::RECURSION)
	{
		Point masterTileSize = { tileSize.x * 3, tileSize.y * 3 };
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
			SDL_RenderDrawLine(screen, boardPosition.x, y, boardPosition.x + mLogic->BoardWidth() * tileSize.x, y);
		}

		for (int tx = 0; tx <= 3; ++tx)
		{
			int x = boardPosition.x + tx * masterTileSize.x;
			SDL_RenderDrawLine(screen, x, boardPosition.y, x, boardPosition.y + mLogic->BoardHeight() * tileSize.y);
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
		destRect.x = mPointerCoords.x * tileSize.x + boardPosition.x;
		destRect.y = mPointerCoords.y * tileSize.y + boardPosition.y;
		destRect.w = tileSize.x;
		destRect.h = tileSize.y;
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
