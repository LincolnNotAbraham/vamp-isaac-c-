
#include <iostream>
#include "game.h"


game* neogame = nullptr; //ponteiro nulo para evitar problemas 


int main(int argc, char* argv[])
{

	const int fps = 60;
	const int frameDelay = 1000 / fps;


	Uint32 frameStart;
	int frameTime;


	neogame = new game(); //coloca no heat, nao na stack
	neogame->init("ahh", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1550, 800, true);






	while (neogame->running())  //via ponteiro
	{  //tudo q etsa abaixo vai ser atualizado toda hora


		if (!neogame->pause())
		{
			frameStart = SDL_GetTicks();

			neogame->handleEvents();
			neogame->update();
			neogame->render();



			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime)
			{
				SDL_Delay(frameDelay - frameTime); //16 = aproiximadaemnte 60fps
				
			}
		}



		
	}

	neogame->clean(); //fecha o jogo

	delete neogame; //deekter ao hat criado












	return 0;
}