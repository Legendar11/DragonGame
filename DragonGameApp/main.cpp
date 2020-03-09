
#include <ctime>
#define __USE_MINGW_ANSI_STDIO 0
#include "SDL_Game.h"


int main(int argc, char* args[])
{
	srand(time(NULL));

	SDL_Game* game = new SDL_Game("Drakon", 25);

	game->Render();

	SDL_Event event;
	bool quit = false;

	while (!quit)
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;

			game->CheckEventKeyboard();

			SDL_PumpEvents(); // обработчик событий.

			game->Render();
		}


	SDL_Quit();
	return 1;
}
