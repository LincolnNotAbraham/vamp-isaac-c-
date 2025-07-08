#pragma once
#include "SDL2/SDL.h"         
#include "SDL2/SDL_image.h"  
 

class inimigo
{

public:

	inimigo(SDL_Renderer* renderer, int x, int y, const char* texturePath);
	~inimigo();

	void update(int playerX, int playerY);
	void render(SDL_Renderer* renderer, int renderX, int renderY);

	// Getter para dstRect - Essencial para game.cpp

	virtual int getVida() const;

	virtual void levarDano(int dano);

	int getXp() { return xp; };

	SDL_Rect getDstRect() const;

	int getDamage() { return damage; }

protected:

	int xp;
	int damage;
	int vida;
	SDL_Texture* enemyText;
	SDL_Rect srcRect, dstRect;
	float speed;


};
//============================================================================================
//                              classes derivadas
// ========================================================================
class zombie : public inimigo
{
public:

	zombie(SDL_Renderer* renderer, int x, int y);
	~zombie();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:
	

};


class esqueleto : public inimigo
{

public:
	esqueleto(SDL_Renderer* renderer, int x, int y);
	~esqueleto();

	//void update(int playerX, int playerY) override;

	//void levarDano(int dano)override;
	//int getVida()override;

protected:


};


class bat : public inimigo
{
public:

	bat(SDL_Renderer* renderer, int x, int y);
	~bat();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:


};




class golem : public inimigo
{
public:

	golem(SDL_Renderer* renderer, int x, int y);
	~golem();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:

};


class fantasma : public inimigo
{
public:

	fantasma(SDL_Renderer* renderer, int x, int y);
	~fantasma();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:


};

class fogo : public inimigo
{
public:

	fogo(SDL_Renderer* renderer, int x, int y);
	~fogo();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:





};



class bispo : public inimigo
{
public:

	bispo(SDL_Renderer* renderer, int x, int y);
	~bispo();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:


};


class olho : public inimigo
{
public:

	olho(SDL_Renderer* renderer, int x, int y);
	~olho();

	//void update(int playerX, int playerY) override;
	//int getVida()override;
	//void levarDano(int dano)override;

private:


};