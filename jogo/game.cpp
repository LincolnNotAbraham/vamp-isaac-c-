#include "game.h"
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <iomanip> 



std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<> spawn1000(1300, 2000);
std::uniform_int_distribution<> spawnDist(-200, 1250);
std::uniform_int_distribution<> sideDist(0, 3);
std::uniform_int_distribution<> UpgradesEscolha(0, 9);



game::game()
{
	lastShoot = 0; //milisegundos
	timeDamage = 0;
	camera = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
	mapText = nullptr;
	gameFont = nullptr;
	escolhaText = nullptr;
	startText = nullptr;
	gameoverText = nullptr;

	
	

}

game::~game()
{
	// limpar projeteis
	for (projetil* proj : projeteis) {
		delete proj;
	}
	projeteis.clear();

	// limpar inimigos
	for (inimigo* inimigop : inimigos) {
		delete inimigop;
	}
	inimigos.clear();

	//for (xpGem* gem : gemas) {
//		delete gem;
//	}
//	gemas.clear();


	// Deletar o player
	//delete gamePlayer;
}


void game::init(const char* title, int x, int y, int width, int heigth, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		//flags = SDL_WINDOW_FULLSCREEN;
	}




	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //verifica se ja foi incializado
	{
		std::cout << "Sistema inicializado" << std::endl;

		window = SDL_CreateWindow(title, x, y, width, heigth, flags); //cria uma janela
		if (window) //janela foi criada?
		{
			std::cout << "janela criada" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0); //da valor ao rrenderer declarado anteriormennte

		if (renderer)//render foi criado?
		{
			//SDL_SetRenderDrawColor(renderer, 133, 133, 133, 255); //azul calro
			std::cout << "render criada" << std::endl;

		}

		if (TTF_Init() == -1)
		{
			std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
		}



		//inicalizar o sdl image
		int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG; // Adiciona suporte a JPG e PNG
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			std::cerr << "SDL_image não pôde ser inicializado! Erro SDL_image: " << IMG_GetError() << std::endl;
			isRunning = false; // Se a inicialização falhar, o jogo não pode continuar
			return; // Sai da função init
		}
		else {
			std::cout << "SDL_image inicializado com sucesso." << std::endl;
		}







		//textura da merda do tilset
		SDL_Surface* tempSurface2 = IMG_Load("assets/chao3.png");
		if (!tempSurface2) {
			std::cerr << "Erro ao carregar imagem assets/chao2.jpg: " << IMG_GetError() << std::endl;
			
		}
		mapText = SDL_CreateTextureFromSurface(renderer, tempSurface2);
		SDL_FreeSurface(tempSurface2);


		// inicalizar fonte do jogo
		gameFont = TTF_OpenFont("assets/font.ttf", 24);

		if (gameFont == nullptr) {
			std::cerr << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;

		}

		SDL_Surface* tempsurface = IMG_Load("assets/escolha.png");
		escolhaText = SDL_CreateTextureFromSurface(renderer, tempsurface);
		SDL_FreeSurface(tempsurface);


		SDL_Surface* tempsurface3 = IMG_Load("assets/start.png");
		startText = SDL_CreateTextureFromSurface(renderer, tempsurface3);
		SDL_FreeSurface(tempsurface3);


		SDL_Surface* tempsurface4 = IMG_Load("assets/gameover.png");
		gameoverText = SDL_CreateTextureFromSurface(renderer, tempsurface4);
		SDL_FreeSurface(tempsurface4);
	
		startDstRect.w = width;
		startDstRect.h = heigth;


		SDL_Event evento3;

		while (true)
		{
			std::cout << "tste" << "\n";

			SDL_PollEvent(&evento3);  //verifica se ouve algum eventi(clique, teclado..)

			SDL_RenderCopy(renderer, startText, &startSrcRect, &startDstRect);

			if (evento3.type == SDL_MOUSEBUTTONDOWN) 
			{
				break;
			}

			SDL_RenderPresent(renderer);

		}

		largura = width;
		altura - heigth;
		isRunning = true;
		isPause = false;





		gamePlayer = new player(renderer, width/2 , heigth/2); //posição inical

		/*
		nextEsqueletoSpawnTime = SDL_GetTicks();
		nextZombieSpawnTime = SDL_GetTicks();
		nextBatSpawnTime = SDL_GetTicks(); 
		nextGolemSpawnTime = SDL_GetTicks();
		*/

		upgrades.push_back("Damage UP");
		upgrades.push_back("Fire Rate UP");
		upgrades.push_back("Range UP");
		upgrades.push_back("Life UP");
		upgrades.push_back("Size UP");
		upgrades.push_back("+Life -Size");
		upgrades.push_back("+Fire Rate -Damage");
		upgrades.push_back("+Damage -Speed");
		upgrades.push_back("+Fire Rate -Range");
		upgrades.push_back("Speed UP");







		descri.push_back("Aumenta o dano");
		descri.push_back("Aumenta a cadência de disparo");
		descri.push_back("Aumenta a distância de alcance do disparo");
		descri.push_back("Aumenta a vida total");
		descri.push_back("Aumenta o tamanho do projetil");


	//	todosUpgrades.push_back(



	}




	else {
		isRunning = false;



	}


}



bool checkCollision(const SDL_Rect& a, const SDL_Rect& b)

{
	return (a.x<b.x + b.w &&
		a.x + a.w>b.x &&
		a.y< b.y + b.h &&
		a.y + a.h > b.y);
}


void game::handleEvents()
{
	//criou variavel evento da classe sdl_event e passa no poll event como referencia 
	const Uint8* state = SDL_GetKeyboardState(NULL);


	gamePlayer->movCima = state[SDL_SCANCODE_W];
	gamePlayer->movBaixo = state[SDL_SCANCODE_S];
	gamePlayer->movEsquerda = state[SDL_SCANCODE_A];
	gamePlayer->movDireita = state[SDL_SCANCODE_D];

	if (SDL_GetTicks() - lastShoot >= gamePlayer->Pshootcooldown)
	{

		float playerCenterX = gamePlayer->getDstRect().x + gamePlayer->getDstRect().w / 2.0f; //posção central do player
		float playerCenterY = gamePlayer->getDstRect().y + gamePlayer->getDstRect().h / 2.0f;



		float dirX = 0.0f;
		float dirY = 0.0f;


		if (state[SDL_SCANCODE_UP]) dirY = -1;

		if (state[SDL_SCANCODE_DOWN]) dirY = 1;

		if (state[SDL_SCANCODE_LEFT]) dirX = -1;

		if (state[SDL_SCANCODE_RIGHT]) dirX = 1;




		/*
		switch (evento.key.keysym.sym)
		{
		case SDLK_UP:     dirY = -1; break;
		case SDLK_DOWN:   dirY = 1; break;
		case SDLK_LEFT:   dirX = -1; break;
		case SDLK_RIGHT:  dirX = 1; break;
		default: break;
		}
		*/

		//se foi atirado , ie: direção nao é zero


		if (dirX != 0 || dirY != 0)
		{
			projeteis.push_back(new projetil(renderer, playerCenterX, playerCenterY,
				gamePlayer->Pshootspeed , gamePlayer->Pdamage, dirX, dirY,
				gamePlayer->Pshootsize, 255, 255, 0, 255, gamePlayer->Prange, "assets/bullet.png"));

			lastShoot = SDL_GetTicks(); // Atualiza o tempo do último tiro
		}

	}


		SDL_Event evento;
		SDL_PollEvent(&evento);  //verifica se ouve algum eventi(clique, teclado..)






		switch (evento.type)
		{
		case SDL_QUIT: //evento for fechar a ajneal
			isRunning = false;
			break;

		case SDL_KEYDOWN:

			break;

		default:
			break;
		}

		//gamePlayer->handleMovementWithState();

	
}



void game::update() //nao ter toda a logica do jogo aqui, mas sim apenas os objetos para serem atualizados
{

	Uint32 currentTime = SDL_GetTicks();

	gamePlayer->update();
	//gamePlayer->handleMovementWithState();


	// logica da camera seguir o player 

	//

	camera.x = gamePlayer->getDstRect().x - (SCREEN_WIDTH / 2) + (gamePlayer->getDstRect().w / 2) -180;
	camera.y = gamePlayer->getDstRect().y - (SCREEN_HEIGHT / 2) + (gamePlayer->getDstRect().h / 2) +180;

					//limite camera
	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > MAP_WIDTH - camera.w) camera.x = MAP_WIDTH - camera.w;
	if (camera.y > MAP_HEIGHT - camera.h) camera.y = MAP_HEIGHT - camera.h;





	// logica de spawn de Esqueletos

	if (currentTime >= nextEsqueletoSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda (0=cima, 1=direita, 2=baixo, 3=esquerda)

		

		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}

		inimigos.push_back(new esqueleto(renderer, spawnX, spawnY));
		nextEsqueletoSpawnTime = currentTime + ESQUELETO_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
		ESQUELETO_SPAWN_INTERVAL_MS -= 100;

	}


	// logica de spawn de Zumbis

	if (currentTime >= nextZombieSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda

		// Calcula a posição de spawn fora da tela
		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new zombie(renderer, spawnX, spawnY));
		nextZombieSpawnTime = currentTime + ZOMBIE_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
		ZOMBIE_SPAWN_INTERVAL_MS -= 200;
		if (ZOMBIE_SPAWN_INTERVAL_MS <= 500)
		{
			ZOMBIE_SPAWN_INTERVAL_MS = 1000000;
		}
	
	
	}

	//logica de spwn de bat

	if (currentTime >= nextBatSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda

		// Calcula a posição de spawn fora da tela
		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new bat(renderer, spawnX, spawnY));
		nextBatSpawnTime = currentTime + BAT_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
	
		BAT_SPAWN_INTERVAL_MS -= 150;
		if (BAT_SPAWN_INTERVAL_MS <= 400)
		{
			BAT_SPAWN_INTERVAL_MS = 1000000;
		}
	
	
	}

	//logica spawn golem 


	if (currentTime >= nextGolemSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda

		
		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new golem(renderer, spawnX, spawnY));
		nextGolemSpawnTime = currentTime + GOLEM_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
	}

	//logica spwn olho

	if (currentTime >= nextOlhoSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda


		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new olho(renderer, spawnX, spawnY));
		nextOlhoSpawnTime = currentTime + OLHO_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
	}

	//logica spawn fogo
	if (currentTime >= nextFogoSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda


		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new fogo(renderer, spawnX, spawnY));
		nextFogoSpawnTime = currentTime + FOGO_SPAWN_INTERVAL_MS;

		FOGO_SPAWN_INTERVAL_MS -= 300;
		if (FOGO_SPAWN_INTERVAL_MS <= 350)
		{
			FOGO_SPAWN_INTERVAL_MS = 1000000;
		}
 	}

	//logica spawn bispo

	if (currentTime >= nextBispoSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda


		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new bispo(renderer, spawnX, spawnY));
		nextBispoSpawnTime = currentTime + BISPO_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
	}

	//logica spawn fantasma

	if (currentTime >= nextFantasmaSpawnTime) {
		int spawnX, spawnY;
		int side = sideDist(gen); // Escolhe uma borda


		if (side == 0) { // topo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y - spawn1000(gen); // Acima da tela
		}

		else if (side == 1) { // Direita
			spawnX = gamePlayer->getDstRect().x + spawn1000(gen); // À direita da tela
			spawnY = spawnDist(gen);
		}
		else if (side == 2) { // Baixo
			spawnX = spawnDist(gen);
			spawnY = gamePlayer->getDstRect().y + spawn1000(gen); // Abaixo da tela
		}
		else { // Esquerda
			spawnX = gamePlayer->getDstRect().x - spawn1000(gen); // À esquerda da tela
			spawnY = spawnDist(gen);
		}
		inimigos.push_back(new fantasma(renderer, spawnX, spawnY));
		nextFantasmaSpawnTime = currentTime + FANTASMA_SPAWN_INTERVAL_MS; // Define o próximo tempo de spawn
	}











	for (inimigo* inimigop : inimigos)
	{
		inimigop->update(gamePlayer->getDstRect().x, gamePlayer->getDstRect().y);

		SDL_Rect q = inimigop->getDstRect();
		SDL_Rect z = gamePlayer->getDstRect();

		if (SDL_HasIntersection(&z, &q) && (SDL_GetTicks() - timeDamage >= invencibleTime) )
		{
			gamePlayer->levarDano(inimigop->getDamage());
			timeDamage = SDL_GetTicks();

			std::cout << "levou dano, vida atual:" << gamePlayer->getVida() << "\n";

		}




	}


	for (projetil* proj : projeteis) 
	{
		proj->update();

		for (inimigo* inimigo : inimigos)
		{
			SDL_Rect q = inimigo->getDstRect();
			SDL_Rect z = proj->getDstRect();

			if (SDL_HasIntersection(&z, &q))
			{

				inimigo->levarDano(gamePlayer->Pdamage);

				if (inimigo->getVida() <= 0)
				{
					gemas.push_back(new xpGem(renderer, "assets/gem.png", inimigo->getDstRect().x, inimigo->getDstRect().y,
						inimigo->getXp()));
					std::cout << "gema criada na posiçao " << "\n";
				}

				//excluir projetil
				if (!gamePlayer->getPiercing())
				{
					auto it = std::find(projeteis.begin(), projeteis.end(), proj);

					if (it != projeteis.end())
					{
						projeteis.erase(it);
					}
				}
				
			}
				
		}
	}



	for (xpGem* gem : gemas)
	{
		SDL_Rect q = gem->getDstRect();
		SDL_Rect z = gamePlayer->getDstRect();

		if (SDL_HasIntersection(&z, &q))
		{
			auto it = std::find(gemas.begin(), gemas.end(), gem);

			if (it != gemas.end())
			{
				std::cout  << gem->getValor();
				gamePlayer->setxp(gem->getValor());
				gemas.erase(it);
			}
		}

		gem->seguirPlayer(gamePlayer->getDstRect().x, gamePlayer->getDstRect().y); // ja tem o if na funcao da classe

	}

	projeteis.erase(std::remove_if(projeteis.begin(), projeteis.end(),
		[](projetil* p) {
			if (!p->isActive()) {
				delete p; // Libera a memória do projétil inativo
				return true; // Marca para remoção do vetor
			}
			return false;
		}),
		projeteis.end());
	

	inimigos.erase(std::remove_if(inimigos.begin(), inimigos.end(),
		[](inimigo* m)
		{
			if (m->getVida() <= 0)
			{
				delete m;
				return true;
			}
			return false;

		}), inimigos.end());
	

	px = gamePlayer->getDstRect().x;
	py = gamePlayer->getDstRect().y;



	//Sistemas de upgrades e level up


	if (gamePlayer->getXpAtual() >= gamePlayer->getXpNext() )
	{
		gamePlayer->levelUp();
		//setJanelaPause(3);
		janelaEscolha(3);
		//isPause = true;
		
		if (upgrade == "Damage UP") 
		{
			std::cout << "dano upado " << "\n";
			gamePlayer->setDamage(7);
		}
		else if (upgrade == "Fire Rate UP") 
		{
			std::cout << "fire rate " << "\n";
			gamePlayer->setshootCooldown(-50);
		}

		else if (upgrade == "Range UP")
		{
			std::cout << "range upado " << "\n";

			gamePlayer->setRange(30);
		}

		else if (upgrade == "Size UP")
		{
			std::cout << "size upado " << "\n";

			gamePlayer->setshootSize(5);
		}

		else if (upgrade == "Life UP")
		{
			std::cout << "life upado " << "\n";

			gamePlayer->setVida(20);
		}

		else if (upgrade == "+Life -Size")
		{
			std::cout << "+Life -Size" << "\n";

			gamePlayer->setVida(30);
			gamePlayer->setshootSize(-5);
		}

		else if (upgrade == "+Fire Rate -Damage")
		{
			std::cout << "+Fire Rate -Damage" << "\n";

			gamePlayer->setDamage(-8);
			gamePlayer->setshootCooldown(-100);
		}

		else if (upgrade == "+Damage -Speed")
		{
			std::cout << "+Damage -Speed" << "\n";

			gamePlayer->setDamage(10);
			gamePlayer->setSpeed(-1);
		}

		else if (upgrade == "+Fire Rate -Range")
		{
			std::cout << "+Fire Rate -Range" << "\n";

			gamePlayer->setshootCooldown(-70);
			gamePlayer->setRange(-80);
		}

		else if (upgrade == "Speed UP")
		{
			std::cout << "Speed UP" << "\n";

			gamePlayer->setSpeed(1);
		
		}
		

		/*
		upgrades.push_back("Damage UP");
		upgrades.push_back("Fire Rate UP");
		upgrades.push_back("Range UP");
		upgrades.push_back("Life UP");
		upgrades.push_back("Size UP");
		*/


	}








	if (gamePlayer->getVida() <= 0 )
	{
		std::cout << "vida 0 " << "\n";


		while (true)
		{
			std::cout << "game overau" << "\n";

			SDL_RenderClear(renderer);

		
			SDL_RenderCopy(renderer, gameoverText, &goSrcRect, &goDstRect);


			SDL_RenderPresent(renderer);

		}


		//isPause = true;
	}






}



void game::render()
{



	SDL_GetWindowSize(window, &largura, &altura);
	//SDL_SetRenderDrawColor(renderer, 133, 133, 133, 255); 
	SDL_RenderClear(renderer); //limpar o buffer 

	// incio rnderaçzao tileset visiveis;(
	//int startTileX = camera.x / TILE_SIZE;
	//int startTileY = camera.y / TILE_SIZE;

//	int endTileX = (camera.x + camera.w) / TILE_SIZE;
//	int endTileY = (camera.y + camera.h) / TILE_SIZE;




	for (int yu = 0; yu < MAP_TILES_Y; yu++)
	{
		for (int xu = 0; xu < MAP_TILES_X; xu++)
		{
			SDL_Rect srcRectTile = { 0,0,TILE_SIZE,TILE_SIZE };


			SDL_Rect dstRectTile = {
				(xu * TILE_SIZE) - camera.x,
				(yu * TILE_SIZE) - camera.y,
				TILE_SIZE,
				TILE_SIZE
			};
			SDL_RenderCopy(renderer, mapText, &srcRectTile, &dstRectTile);



		}
	}



	//gamePlayer->render(renderer);
	
	// ================================
	//           debug de hitbox
	// ============================
//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//	SDL_Rect gameplayerDST = gamePlayer->getDstRect();
//	SDL_RenderDrawRect(renderer, &gameplayerDST);
//	SDL_SetRenderDrawColor(renderer, 133, 133, 133, 255);
	//=====================================================

	for (inimigo* inimigop : inimigos)
	{
		SDL_Rect enemyRenderRect = inimigop->getDstRect(); 
		enemyRenderRect.x -= camera.x; 
		enemyRenderRect.y -= camera.y; 


		inimigop->render(renderer, enemyRenderRect.x, enemyRenderRect.y);
		// ================================
		//           debug de hitbox
		// ============================
	//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//	SDL_Rect rectTESTEenemy = inimigop->getDstRect();
	//	SDL_RenderDrawRect(renderer, &rectTESTEenemy);
	//	SDL_SetRenderDrawColor(renderer, 133, 133, 133, 255);
		//=====================================================
	}

	for (projetil* proj : projeteis) {

		SDL_Rect projRenderRect = proj->getDstRect(); // Posição do projétil no MUNDO
		projRenderRect.x -= camera.x; // Ajusta para a posição na tela
		projRenderRect.y -= camera.y; // Ajusta para a posição na tela


		proj->render(renderer, projRenderRect.x, projRenderRect.y);

		// ================================
		//           debug de hitbox
		// ============================
	//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//	SDL_Rect rectTESTEproj = proj->getDstRect();
	//	SDL_RenderDrawRect(renderer, &rectTESTEproj);
	//	SDL_SetRenderDrawColor(renderer, 133, 133, 133, 255);
		//=====================================================
	}


	for (xpGem* gem : gemas) 
	{

		SDL_Rect projRenderRect = gem->getDstRect(); // 
		projRenderRect.x -= camera.x; // 
		projRenderRect.y -= camera.y; 


		gem->render(renderer, projRenderRect.x, projRenderRect.y);

	}



	SDL_Rect playerRenderRect = gamePlayer->getDstRect();
	playerRenderRect.x -= camera.x;
	playerRenderRect.y -= camera.y;
	gamePlayer->render(renderer, playerRenderRect.x, playerRenderRect.y);








	//=============================================
	//				textos
	//===========================================

	
	//vida
	SDL_Color textcolor = { 255,50,30,255 };
	std::string vidaText = "Vida: " + std::to_string(gamePlayer->getVida());
	SDL_Texture* vidatexture = loadTextTexture(renderer, vidaText.c_str(), gameFont, textcolor);

	if (vidatexture)
	{
		int textW, textH;
		SDL_QueryTexture(vidatexture, nullptr, nullptr, &textW, &textH);
		SDL_Rect textRect = {10, 10, textW, textH }; // Posição (10,10) na tela
		SDL_RenderCopy(renderer, vidatexture, nullptr, &textRect);
		SDL_DestroyTexture(vidatexture); // Liberar a textura depois de usá-la
	}

	//xp

	SDL_Color xpcolor = { 20,250,30,255 };
	std::string xpText = "XP: " + std::to_string(gamePlayer->getXpAtual());
	SDL_Texture* xptexture = loadTextTexture(renderer, xpText.c_str(), gameFont, xpcolor);

	if (vidatexture)
	{
		int textWx, textHx;
		SDL_QueryTexture(xptexture, nullptr, nullptr, &textWx, &textHx);
		SDL_Rect xpRect = { 10, 40, textWx, textHx }; // Posição (10,10) na tela
		SDL_RenderCopy(renderer, xptexture, nullptr, &xpRect);
		SDL_DestroyTexture(xptexture); // Liberar a textura depois de usá-la
	}


	//damage

	SDL_Color damcolor = { 1,1,1,255 };
	std::string damText = std::to_string(gamePlayer->Pdamage) + " Damage" ;
	SDL_Texture* damtexture = loadTextTexture(renderer, damText.c_str(), gameFont, damcolor);

	if (damtexture)
	{
		int textWd, textHd;
		SDL_QueryTexture(damtexture, nullptr, nullptr, &textWd, &textHd);
		SDL_Rect damRect = { 10, 100, textWd, textHd }; 
		SDL_RenderCopy(renderer, damtexture, nullptr, &damRect);
		SDL_DestroyTexture(damtexture); // Liberar a textura depois de usá-la
	}


	//Firerate

//	SDL_Color damcolor = { 1,1,1,255 };
	int cx = 1000 / gamePlayer->Pshootcooldown;
	std::string frText = std::to_string(cx) + " Fire Rate";
	SDL_Texture* frtexture = loadTextTexture(renderer, frText.c_str(), gameFont, damcolor);


	int textWf, textHf;
	SDL_QueryTexture(frtexture, nullptr, nullptr, &textWf, &textHf);
	SDL_Rect frRect = { 10, 140, textWf, textHf };
	SDL_RenderCopy(renderer, frtexture, nullptr, &frRect);
	SDL_DestroyTexture(frtexture); // Liberar a textura depois de usá-la
	


	//range

//	SDL_Color damcolor = { 1,1,1,255 };
	std::string ranText = std::to_string(gamePlayer->Prange) + " Range";
	SDL_Texture* rantexture = loadTextTexture(renderer, ranText.c_str(), gameFont, damcolor);

	
	int textWr, textHr;
	SDL_QueryTexture(rantexture, nullptr, nullptr, &textWr, &textHr);
	SDL_Rect rRect = { 10, 180, textWr, textHr };
	SDL_RenderCopy(renderer, rantexture, nullptr, &rRect);
	SDL_DestroyTexture(rantexture); // Liberar a textura depois de usá-la
	

	// shoot Size

//	SDL_Color damcolor = { 1,1,1,255 };
	std::string sizeText = std::to_string(gamePlayer->Pshootsize) + " Shoot Size";
	SDL_Texture* sizetexture = loadTextTexture(renderer, sizeText.c_str(), gameFont, damcolor);


	int textWs, textHs;
	SDL_QueryTexture(sizetexture, nullptr, nullptr, &textWs, &textHs);
	SDL_Rect sizeRect = { 10, 220, textWs, textHs };
	SDL_RenderCopy(renderer, sizetexture, nullptr, &sizeRect);
	SDL_DestroyTexture(sizetexture); // Liberar a textura depois de usá-la

	// speed

//	SDL_Color damcolor = { 1,1,1,255 };
	std::string speedText = std::to_string(gamePlayer->getSpeed()) + " Speed";
	SDL_Texture* speedtexture = loadTextTexture(renderer, speedText.c_str(), gameFont, damcolor);
	

	int textWss, textHss;
	SDL_QueryTexture(speedtexture, nullptr, nullptr, &textWss, &textHss);
	SDL_Rect speedRect = { 10, 260, textWss, textHss };
	SDL_RenderCopy(renderer, speedtexture, nullptr, &speedRect);
	SDL_DestroyTexture(speedtexture); // Liberar a textura depois de usá-la


	// tempo de jogo

//	SDL_Color damcolor = { 1,1,1,255 };
	std::string timeText = std::to_string(SDL_GetTicks()/100);
	SDL_Texture* timetexture = loadTextTexture(renderer, timeText.c_str(), gameFont, damcolor);


	int textWtime, textHtime;
	SDL_QueryTexture(timetexture, nullptr, nullptr, &textWtime, &textHtime);
	SDL_Rect timeRect = {largura/2, 10, textWtime, textHtime };
	SDL_RenderCopy(renderer, timetexture, nullptr, &timeRect);
	SDL_DestroyTexture(timetexture); // Liberar a textura depois de usá-la












	SDL_RenderPresent(renderer);
}



SDL_Texture* game::loadTextTexture(SDL_Renderer* renderer, const char* text, TTF_Font* font, SDL_Color color) {
	if (!font) {
		std::cerr << "Erro: Fonte TTF_Font* é nullptr em loadTextTexture." << std::endl;
		return nullptr;
	}

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
	if (textSurface == nullptr) {
		std::cerr << "Erro ao renderizar texto: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture == nullptr) {
		std::cerr << "Erro ao criar textura do texto: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(textSurface); // Liberar a superfície, pois a textura já foi criada
	return textTexture;
}




void game::janelaEscolha(int janelaEscolhida)
{


	std::cout << "entrou primeiro" << "\n";

	switch (janelaEscolhida)
	{
	case 0:
		std::cout << "entrou 0" << "\n";

		break;


	case 1:
		std::cout << "entrou 1" << "\n";

		//start
		break;


	case 2:
		//game over
		break;

	case 3:

		std::cout << "entrou 3" << "\n";


		//janela de escolhas upgrades
		w1 = UpgradesEscolha(gen);
		w2  = UpgradesEscolha(gen);
		w3 = UpgradesEscolha(gen);

		SDL_Event e;

		while (true)
		{

			//SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, escolhaText, &EsrcRect, &EdstRect);


			//upgrade 1
		

			SDL_Color textcolor1 = { 255,255,255,255 };
			std::string Up1Text = upgrades[w1];
			SDL_Texture* up1texture = loadTextTexture(renderer, Up1Text.c_str(), gameFont, textcolor1);

			if (up1texture)
			{
				int textW, textH;
				SDL_QueryTexture(up1texture, nullptr, nullptr, &textW, &textH);
				SDL_Rect textRect = { 480, 200 , textW, textH };
				SDL_RenderCopy(renderer, up1texture, nullptr, &textRect);
				SDL_DestroyTexture(up1texture);
			}
			//upgrade 2

			

			SDL_Color textcolor2 = { 255,255,255,255 };
			std::string Up2Text = upgrades[w2];
			SDL_Texture* up2texture = loadTextTexture(renderer, Up2Text.c_str(), gameFont, textcolor2);

			if (up2texture)
			{
				int textW, textH;
				SDL_QueryTexture(up2texture, nullptr, nullptr, &textW, &textH);
				SDL_Rect textRect = {480, 350 , textW, textH };
				SDL_RenderCopy(renderer, up2texture, nullptr, &textRect);
				SDL_DestroyTexture(up2texture);
			}


		
			//upgrade 3
		
			SDL_Color textcolor3 = { 255,255,255,255 };
			std::string Up3Text = upgrades[w3];
			SDL_Texture* up3texture = loadTextTexture(renderer, Up3Text.c_str(), gameFont, textcolor3);

			if (up3texture)
			{
				int textW, textH;
				SDL_QueryTexture(up3texture, nullptr, nullptr, &textW, &textH);
				SDL_Rect textRect = { 480, 500 , textW, textH };
				SDL_RenderCopy(renderer, up3texture, nullptr, &textRect);
				SDL_DestroyTexture(up3texture);
			}



			SDL_PollEvent(&e);

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				int mouseX = e.button.x;
				int mouseY = e.button.y;

				std::cout << mouseX << mouseY << "\n";

				if (mouseY > 170 && mouseY < 240)
				{
					std::cout << "escolheu o primeiro upgrade" << "\n";
					upgrade = upgrades[w1];
					return;
				}

				if (mouseY > 330 && mouseY <400)
				{
					std::cout << "escolheu o segundo upgrade upgrade" << "\n";
					upgrade = upgrades[w2];

					return;
				}

				if (mouseY >480 && mouseY < 545)
				{

					std::cout << "escolheu o terceiro upgrade upgrade" << "\n";
					upgrade = upgrades[w3];
					return;
				}


			}



			SDL_RenderPresent(renderer);
		}




	}
}




void game::clean()
{



	delete gamePlayer;


	for (inimigo* inimigoPtr : inimigos) {
		delete inimigoPtr;
	}
	inimigos.clear(); // limpa o vetor
	
	for (projetil* proj : projeteis) {
		delete proj;
	}
	projeteis.clear();


	if (mapText)
	{
		SDL_DestroyTexture(mapText);
		mapText = nullptr;
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();


	std::cout << "jogo limpado" << std::endl;
}


//ccondiuração de audio

//SDL_AudioSpec desiredSpec;
//SDL_zero(desiredSpec);
