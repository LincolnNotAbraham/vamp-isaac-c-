#pragma once
#include "SDL2/SDL.h"         
#include "SDL2/SDL_image.h"  
 

class xpGem
{
public:

	xpGem(SDL_Renderer* renderer, const char* texturePath, int x, int y, int valor);
	~xpGem();


	SDL_Rect getDstRect() { return dstRect; };

//	void setAtraida() { atraida = true; }
//	void setNotAtraida() { atraida = false; }
//	bool funcAtraida() { return atraida; }/


	void seguirPlayer(int xp, int yp);
	void render(SDL_Renderer* renderer, int renderX, int renderY);

	int getValor() { return pvalor; }

private:

	SDL_Texture* gemText;

	int x;
	int y;
	int pvalor;
	SDL_Rect dstRect, srcRect;
//	bool atraida = false;

};

