#include "inimigo.h"
#include <iostream>

inimigo::inimigo(SDL_Renderer* renderer, int x, int y, const char* texturePath)
{
	SDL_Surface* tempsurface = IMG_Load(texturePath);
	enemyText = SDL_CreateTextureFromSurface(renderer, tempsurface);
	SDL_FreeSurface(tempsurface);

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 32;
	srcRect.h = 32;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = 64;
	dstRect.h = 64;

	vida = 100;
	speed = 3.0f;


}



inimigo::~inimigo()
{
	SDL_DestroyTexture(enemyText); // playerText deveria ser enemyTexture
}


void inimigo::update(int playerX, int playerY)
{

	//todos inimigos irao seguir o player 



	//posição central do inimigo
	float centerX = dstRect.x;  //+ dstRect.w ;
	float centerY = dstRect.y; //+ dstRect.h ;

	float deltaX = playerX - centerX;
	float deltaY = playerY - centerY;

	float distancia = std::sqrt(deltaX * deltaX + deltaY * deltaY); //"pitagoras" ;-;

	if (distancia > 0.0f)
		{
		//normalizar vetor para fazer a velociade normal

		float direcaoX = deltaX / distancia;
		float direcaoY = deltaY / distancia;

		//mover o bicho
		dstRect.x += static_cast<int>(direcaoX * speed);
		dstRect.y += static_cast<int>(direcaoY * speed); // da cast para int (divisao resulta em float)

		}

	}
	


void inimigo::render(SDL_Renderer* renderer, int renderX, int renderY)
{
	SDL_Rect renderDst = { renderX, renderY, dstRect.w, dstRect.h };
	SDL_RenderCopy(renderer, enemyText, &srcRect, &renderDst); 
}

void inimigo::levarDano(int dano)
{
	vida -= dano;
}

int inimigo::getVida() const
{
	return vida;
}


SDL_Rect inimigo::getDstRect() const
{
	//SDL_Rect rect;
	//rect.x = static_cast<int>(x);
	//rect.y = static_cast<int>(y);
	//rect.w = 64;
//	rect.h = 64;

	return dstRect;
}





//--------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
//                                     classes derivadas 
// ------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------


zombie::zombie(SDL_Renderer* renderer, int x, int y)
	: inimigo (renderer, x, y, "assets/zumbi.png")

{
	vida = 50;
	speed = 3.0f;
	damage = 10;
	//ajustar sprites se necessario
	
	srcRect.w = 29;
	srcRect.h = 46;
	dstRect.w = 55;
	dstRect.h = 100;
	xp = 25;
}

/*
void zombie::update(int playerX, int playerY)
{
	inimigo::update(playerX, playerY);
}
*/


/*
zombie::~zombie()
{
	inimigo::~inimigo();
}
*/





esqueleto::esqueleto(SDL_Renderer* renderer, int x, int y)
	: inimigo(renderer, x, y, "assets/esqueleto.png")

{
	vida = 30;
	speed = 4.0f;
	damage = 7;

	//ajustar sprites se necessario

	 srcRect.w = 22;
	 srcRect.h = 22;
	 dstRect.w = 46;
	 dstRect.h = 46;
	 xp = 15;

}

/*
void esqueleto::update(int playerX, int playerY)
{
	//inimigo::update(playerX, playerY);
}
*/



bat::bat(SDL_Renderer* renderer, int x, int y)
	:inimigo(renderer, x, y, "assets/bat.png")
{
	vida = 15;
	speed = 4.5f;
	damage = 5;
	xp = 5;

	//ajustar sprites se necessario

	srcRect.w = 63;
	srcRect.h = 43;
	dstRect.w = 30;
	dstRect.h = 30;

}



golem::golem(SDL_Renderer* renderer, int x, int y)
	:inimigo(renderer, x, y, "assets/golem.png")
{
	vida = 800;
	speed = 2.0f;
	damage = 20;

	xp = 300;
	//ajustar sprites se necessario

	srcRect.w = 527;
	srcRect.h = 700;
	dstRect.w = 120;
	dstRect.h = 120;
}



fantasma::fantasma(SDL_Renderer* renderer, int x, int y)
	:inimigo(renderer, x, y, "assets/fantasma.png")
{
	vida = 150;
	speed = 3.0f;
	damage = 15;

	xp = 30;
	//ajustar sprites se necessario

	srcRect.w = 64;
	srcRect.h = 48;
	dstRect.w = 80;
	dstRect.h = 60;
}


fogo::fogo(SDL_Renderer* renderer, int x, int y)
	:inimigo(renderer, x, y, "assets/fogo.png")
{
	vida = 5;
	speed = 5.0f;
	xp = 4;
	damage = 5;

	//ajustar sprites se necessario

	srcRect.w = 125;
	srcRect.h = 200;
	dstRect.w = 25;
	dstRect.h = 20;
}

bispo::bispo(SDL_Renderer* renderer, int x, int y)
	:inimigo(renderer, x, y, "assets/bispo.png")
{
	vida = 5000;
	speed = 3.0f;
	damage = 30;
	xp = 5000;
	//ajustar sprites se necessario

	srcRect.w = 300;
	srcRect.h = 530;
	dstRect.w = 100;
	dstRect.h = 180;
}


olho::olho(SDL_Renderer* renderer, int x, int y)
	:inimigo(renderer, x, y, "assets/olho.png")
{
	vida = 300;
	speed = 2.0f;
	xp = 70;
	damage = 25;

	//ajustar sprites se necessario

	srcRect.w = 460;
	srcRect.h = 460;
	dstRect.w = 70;
	dstRect.h = 70;
}

