#include "xpGem.h"
#include <iostream>


xpGem::xpGem(SDL_Renderer* renderer, const char* texturePath, int x, int y, int valor)
{
    SDL_Surface* tempsurface = IMG_Load(texturePath);
    gemText = SDL_CreateTextureFromSurface(renderer, tempsurface);
    SDL_FreeSurface(tempsurface);

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = 20;
    dstRect.h = 20;

	pvalor = valor;

}



void xpGem::seguirPlayer(int xp, int yp)
{
	//posição central do inimigo
	float centerX = dstRect.x;  //+ dstRect.w ;
	float centerY = dstRect.y; //+ dstRect.h ;

	float deltaX = xp - centerX;
	float deltaY = yp - centerY;

	float distancia = std::sqrt(deltaX * deltaX + deltaY * deltaY); //"pitagoras" ;-;

	if (distancia < 70)
	{
		//normalizar vetor para fazer a velociade normal

		float direcaoX = deltaX / distancia;
		float direcaoY = deltaY / distancia;

		//mover o bicho
		dstRect.x += static_cast<int>(direcaoX * 8);
		dstRect.y += static_cast<int>(direcaoY * 8); // da cast para int (divisao resulta em float)

	}

}

void xpGem::render(SDL_Renderer* renderer, int renderX, int renderY)
{


        SDL_Rect renderDst = { renderX, renderY, dstRect.w, dstRect.h };
        SDL_RenderCopy(renderer, gemText, &srcRect, &renderDst); 

}

