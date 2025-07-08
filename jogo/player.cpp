#include "player.h"
#include <iostream>



player::player(SDL_Renderer* renderer, int x, int y)
{

	SDL_Surface* tempSurface = IMG_Load("assets/person.png");


	playerText = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);


	dstRect.x = x;
	dstRect.y = y;
	dstRect.h =	80; //largura e altura do jigador
	dstRect.w = 50;
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 50; // largura da imaegm
	srcRect.h = 80;



	speed = 6.0f;
	vida = 100;

}


player::~player()
{
	SDL_DestroyTexture(playerText);
}





void player::handleEvents(SDL_Event& evento)
{
 //colcoar movimento nao continuos, ex: espeiasl, item ativavel, consumable
}


void player::update()
	{

	float dx = 0;
	float dy = 0;


	if (movCima) dy -= speed;
	if (movBaixo) dy += speed;
	if (movEsquerda) dx -= speed;
	if (movDireita) dx += speed;


	//notmalizar vetores e fazer pitagoras 

	if (dx != 0 && dy != 0)
	{
		float tamanho = std::sqrt(dx * dx + dy * dy);
		dx = (dx / tamanho) * speed;
		dy = (dy / tamanho) * speed;
	}

	dstRect.x += static_cast<int>(dx);
	dstRect.y += static_cast<int>(dy);

	}


void player::render(SDL_Renderer* renderer, int renderX, int renderY)
{
	SDL_Rect renderDst = { renderX, renderY, dstRect.w, dstRect.h };
	SDL_RenderCopy(renderer, playerText, &srcRect, &renderDst);

}



void player::handleMovementWithState()
{
	//const Uint8* state = SDL_GetKeyboardState(NULL);


	//movCima = state[SDL_SCANCODE_W];
	//movBaixo = state[SDL_SCANCODE_S];
	//movEsquerda = state[SDL_SCANCODE_A];
	//movDireita = state[SDL_SCANCODE_D];

}


void player::levarDano(int dano)
{
	vida -= dano;
}