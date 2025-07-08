#include "projetil.h"
#include <iostream>



projetil::projetil(SDL_Renderer* renderer, float startX, float startY,
    float projSpeed, int projDamage, float dirX, float dirY,
    int psize, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int projRange, const char* texturePath)
{


    SDL_Surface* tempsurface = IMG_Load(texturePath);
    projText = SDL_CreateTextureFromSurface(renderer, tempsurface);
    SDL_FreeSurface(tempsurface);

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 37;
    srcRect.h = 37;

    dstRect.x = startX;
    dstRect.y = startY;
    dstRect.w = psize;
    dstRect.h = psize;




    x = startX;
    y = startY;

    initialX = x;
    initialY = y;

   // psize = size;
    damage = projDamage;
    speed = projSpeed;
    active = true;
    range = projRange;

    colorA = a;
    colorB = b;
    colorG = g;
    colorR = r;

    directionX = dirX;
    directionY = dirY;
}

projetil::~projetil()
{
       
    
}

void projetil::update()
{
    if (!active) return;

    
    x += directionX * speed;
    y += directionY * speed;




    float distancetravel = std::sqrt(
        (x - initialX) * (x - initialX) +
        (y - initialY) * (y - initialY)
    );


    if (distancetravel > range)
    {
        active = false;
        return;
    }

    dstRect.x += static_cast<int>(directionX * speed);
    dstRect.y += static_cast<int>(directionY* speed);
    /*

    float dx = 0;
    float dy = 0;


    if (movCimap) dy -= speed;
    if (movBaixop) dy += speed;
    if (movEsquerdap) dx -= speed;
    if (movDireitap) dx += speed;


    //notmalizar vetores e fazer pitagoras 

    if (dx != 0 && dy != 0)
    {
        float tamanho = std::sqrt(dx * dx + dy * dy);
        dx = (dx / tamanho) * speed;
        dy = (dy / tamanho) * speed;
    }

    dstRect.x += static_cast<int>(dx);
    dstRect.y += static_cast<int>(dy);

    */


}

void projetil::render(SDL_Renderer* renderer, int renderX, int renderY) 
{
    /*
    SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, colorA);

    // cria o rect projetil
    SDL_Rect currentRect;

    currentRect.x = static_cast<int>(x);
    currentRect.y = static_cast<int>(y);
    currentRect.w = psize;
    currentRect.h = psize;

    SDL_RenderFillRect(renderer, &currentRect);
    */
   // render(renderer, projRenderRect.x, projRenderRect.y);
    SDL_Rect renderDst = {renderX, renderY, dstRect.w, dstRect.h};
    SDL_RenderCopy(renderer, projText, &srcRect, &renderDst); // playerText deveria ser enemyTexture

}


SDL_Rect projetil::getDstRect() const
{
    return dstRect;
}

void projetil::shootHandleState()
{


        const Uint8* state = SDL_GetKeyboardState(NULL);

        movCimap = state[SDL_SCANCODE_W];
        movBaixop = state[SDL_SCANCODE_S];
        movEsquerdap = state[SDL_SCANCODE_A];
        movDireitap = state[SDL_SCANCODE_D];

   

}