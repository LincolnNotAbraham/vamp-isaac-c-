#pragma once
#include <cmath>
#include "SDL2/SDL.h"         
#include "SDL2/SDL_image.h"  



class projetil
{

public:

   // Construtor:
   // startX, startY = posi��o inicial (do player)
   // targetX, targetY = posi��o para onde o proj�til deve ir (ex: posi��o do mouse)
   // projSpeed = velocidade do proj�til
   // projDamage = dano do proj�til
   // size = largura e altura do quadrado do proj�til
   // r, g, b, a = componentes de cor do proj�til

    projetil(SDL_Renderer* renderer, float startX, float startY,
        float projSpeed, int projDamage, float dirX, float dirY,
        int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int projRange, const char* texturePath);


	~projetil();

	void update();
	void render(SDL_Renderer* renderer, int renderX, int renderY);

    //getters
    SDL_Rect getDstRect() const;

    bool isActive() const { return active; }
    //int getDamage() const { return damage; }


    //setters
    void desativar() { active = false; }

    void shootHandleState();

private:

    float x, y;
    float initialX, initialY;

    float directionX, directionY; //dire��o


    bool movCimap = false;
    bool movBaixop = false;
    bool movEsquerdap = false;
    bool movDireitap = false;


    float speed;
    int damage ;
    bool active;
    int psize ;
    int range ;

    SDL_Texture* projText;
    SDL_Rect srcRect, dstRect;


    Uint8 colorR, colorG, colorB, colorA;

};

