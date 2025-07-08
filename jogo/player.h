#pragma once
#include "SDL2/SDL.h"         
#include "SDL2/SDL_image.h"  
#include <iostream>
#include <vector>
#include <string>
#include <functional> // Para std::function


class player
{

public:

	player(SDL_Renderer* renderer,  int x, int y);
	~player();


	void handleEvents(SDL_Event& evento);
	void update();
	void render(SDL_Renderer* renderer, int renderX, int renderY);
	void handleMovementWithState();
	void levarDano(int dano);

	// Getter para dstRect - Essencial para game.cpp
	SDL_Rect getDstRect() const { return dstRect; }


	struct attrs 
	{ 
			//int vida = 100;
			float shootspeed = 8 ;
			int damage = 10;
			int size = 15;
			int range = 800;
			int shootcooldown = 10;

	};


	bool getPiercing() { return piercing; }

	int getVida() { return vida; }

	bool getInv() { return invencivel;  }

	int getXpAtual() { return xpAtual; }
	int getXpNext() { return xpNext; }
	int getSpeed() { return speed; }





	bool movCima = false;
	bool movBaixo = false;
	bool movEsquerda = false;
	bool movDireita = false;


	//"setters" para upgrade

	void setxp(int xp) { xpAtual += xp; }
	void levelUp() { nivel += 1; int temp = xpAtual ; xpAtual -= xpNext; xpNext = temp + 5 * pow(1.2, nivel); }
	


	void setDamage(int q) { Pdamage += q; }
	void setRange(int q) { Prange += q; }
	void setshootSize(int q) { Pshootsize += q; }
	void setshootSpeed(int q) { Pshootspeed += q; }

	void setshootCooldown(int q) 
	{ 
		if (q < 0)
		{
			if (Pshootcooldown >= 100)
				Pshootcooldown += q;
		}
		if (q>0)
				Pshootcooldown += q;
	}

	void setVida(int q) { vida += q; }
	void setSpeed(int q) { speed += q; }


	float Pshootspeed = 8;
	int Pdamage = 10;
	int Pshootsize = 15;
	int Prange = 400;
	int Pshootcooldown = 10;


private:

	attrs shootAttrs;





	int nivel = 1;
	int xpAtual = 0;
	int xpNext = 10;
	int xpEscolhas;

	bool invencivel = false;

	int shootcooldown;
	bool piercing = false;

	

	SDL_Rect srcRect, dstRect;


	int vida;
	SDL_Texture* playerText;
	float speed;

};

