#pragma once
#include <iostream>
#include <random>
#include "player.h"
#include <vector>
#include "inimigo.h"
#include "projetil.h"
#include "xpGem.h"
#include "SDL2/SDL.h"         
#include "SDL2/SDL_image.h"  
#include "SDL2/SDL_ttf.h" 



// tamanho tela 
const int SCREEN_WIDTH = 1200; 
const int SCREEN_HEIGHT = 1200; 
// tamanho mapa



const int TILE_SIZE = 256;

const int MAP_TILES_X = 20;
const int MAP_TILES_Y = 20;

const int MAP_WIDTH = MAP_TILES_X  * TILE_SIZE;
const int MAP_HEIGHT = MAP_TILES_Y * TILE_SIZE;







class game
{
public:
	game();
	~game();


	void init(const char* title, int x, int y, int width, int heigth, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void janelaEscolha(int janelaEscolhida);

	void clean();

	//void audio();
	bool running() { return isRunning; }
	bool pause() { return isPause; }
	SDL_Texture* loadTextTexture(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color);
	//bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

	int getJanelaPause() { return janelaPause; }
	int setJanelaPause(int n) { janelaPause = n; }



private:


	TTF_Font* gameFont;
	SDL_Rect camera;
	SDL_Texture* mapText;
	SDL_Texture* escolhaText;
	SDL_Texture* startText;
	SDL_Texture* gameoverText;


	//int titleMap[MAP_TILES_X][MAP_TILES_Y];


	int largura;
	int altura;


	int qtnd;

	int cont = 0;

	
	//int framestart = SDL_GetTicks();

	int px, py;
	int qntdG = 0, qntdZ = 0, qntdE = 0;

	Uint32 nextEsqueletoSpawnTime = 30000;
	Uint32 nextZombieSpawnTime = 0;
	Uint32 nextBatSpawnTime = 50000;
	Uint32 nextGolemSpawnTime = 60000;
	Uint32 nextOlhoSpawnTime = 90000;
	Uint32 nextFogoSpawnTime = 0;
	Uint32 nextBispoSpawnTime = 90000;
	Uint32 nextFantasmaSpawnTime = 190000;




	Uint32 invencibleTime = 500;
	Uint32 timeDamage;


	Uint32 ESQUELETO_SPAWN_INTERVAL_MS = 10000; 
	Uint32 ZOMBIE_SPAWN_INTERVAL_MS = 12000; 
	Uint32 BAT_SPAWN_INTERVAL_MS = 7000;  
	Uint32 GOLEM_SPAWN_INTERVAL_MS = 60000;  
	Uint32 OLHO_SPAWN_INTERVAL_MS = 10000;
	Uint32 BISPO_SPAWN_INTERVAL_MS =180000;
	Uint32 FOGO_SPAWN_INTERVAL_MS = 5000;
	Uint32 FANTASMA_SPAWN_INTERVAL_MS = 12000;


	int janelaPause;

	bool isRunning;
	bool isPause = true;
	int w1,w2,w3;

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::vector<inimigo*> inimigos; //vetorr de inimigos
	std::vector<projetil*> projeteis; //vetor de projetil
	std::vector<xpGem*> gemas;



	std::vector<std::string> upgrades;
	//std::vector<std::function<void(player*, int)>> todosUpgrades; //macacada pill
	std::vector<std::string> descri;

	std::string upgrade;

	player* gamePlayer;

	Uint32 lastShoot; 
	Uint32 shootCooldown;


	//telas


	SDL_Rect EdstRect = { 300, 100, 500,500 };
	SDL_Rect EsrcRect = { 0,0, 500,500 };

	SDL_Rect startSrcRect = { 0,0,579,389 };
	SDL_Rect startDstRect = { 0,0, 500,500 };


	SDL_Rect goSrcRect = { 0,0,1599,899 };
	SDL_Rect goDstRect = { 250,0,1024,576};



};

