#include "tictacwoahapp.h"

#include <random>
#include <time.h>

TicTacWoahApp game;

int main(int argc, char* args[])
{
	srand(time(NULL));

	if (game.Init())
	{
		game.Run();
	}

	game.Shutdown();

	return 0;
}
