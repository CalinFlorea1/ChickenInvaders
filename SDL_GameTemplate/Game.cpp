#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Scoreboard.h"
#include "SDL_mixer.h"
#include "ManangeFiles.h"

struct {
	int chicken;
	int moment;
}MomentsOfShoot[10005];

Map* map;
Player *player;
Enemy* Chicken[2][40];
Bullet* Glont[10000];
Bullet* Eggs[10009];
Bullet* Money[100];
Scoreboard* coin, *coinunitati, *coinzeci, *liveunitati, *live;
ManangeFiles *File;
int IfSaveOrNewGame = 0;
std::vector <Scoreboard*> Litere[15];
std::vector <Scoreboard*> NumePlayerLitere;
int pozFile = -1;

extern int directiex, directiey;
char PlayerNume[50] = "ceva\0";
int contorNume;
char SirPentruNumere[] = "assets/ .png\0";
char SirPentruLitere[] = "assets/Text/ .png\0";
int contorMoney = 0;
int NumberOfLevelsCompleted;
int contorMoneyLuati;
int contorGloante;
int totalScore, LevelScore[5];
int contorEggs;
int Iterator = 0;
int LastLevel;
int ChickenDown;
int Numbers;
Mix_Chunk* BackMusicMenu, *ShotNava, *ChickenHurt, *ExplosionNava, *CoinSound, *WOW;
FileStuff FilesAux;

Game::Game(): isRunning(false), window(nullptr), renderer(nullptr){}

Game::~Game()
{
   delete player;
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window!=nullptr)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	WhatModule = 0;
	InitMainMenu();

	if (Mix_Init(SDL_INIT_AUDIO | MIX_INIT_MOD | MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) != 0) {
		std::cout << "Music Initialized\n";
	}
	else {
		std::cout << "Music doesn't Initialized\n";
		isRunning = false;
	}
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != -1) {
		std::cout << "Open Audio Initialized\n";
	}
	else {
		std::cout << "Open Audio doesn't Initialized\n";
		isRunning = false;
	}
	
	BackMusicMenu = Mix_LoadWAV("assets/MainMenuSong.wav");
	ShotNava = Mix_LoadWAV("assets/Shot.wav");
	ExplosionNava = Mix_LoadWAV("assets/ExplosionNava.wav");
	ChickenHurt = Mix_LoadWAV("assets/ChickenHurt.wav");
	WOW = Mix_LoadWAV("assets/WOW.wav");
	CoinSound = Mix_LoadWAV("assets/CoinSound.wav");

	Mix_PlayChannel(-1, BackMusicMenu, 1000);

	File = new ManangeFiles();
	File->ExportFromFile();
	FilesEntries();
}

void Game :: FilesEntries() {
	int scor, level;
	Numbers = File->OutNumbersOfEntries();
	char* nume = new char[100];
	Numbers = std :: min(Numbers, 10);
	for (int i = 0; i < Numbers; i++) {
		nume = File->ExportNume(i);
		level = File->ExportLevel(i);
		scor = File->ExportScore(i);
		for (int j = 0; nume[j] != 0; j++) {
			if (nume[j] >= 'A' && nume[j] <= 'Z')
				nume[j] = nume[j] - 'A' + 'a';
			SirPentruLitere[12] = nume[j];
			Scoreboard* temp = new Scoreboard(SirPentruLitere, renderer);
			temp->init(260 + (j * 40), 220 + (i * 80), 30);
			Litere[i].push_back(temp);
		}

		SirPentruNumere[7] = (char)(scor / 100 % 10 + '0');
		Litere[i].push_back(new Scoreboard(SirPentruNumere, renderer));
		Litere[i][Litere[i].size() - 1]->init(1200, 200 + (i * 80), 80);

		SirPentruNumere[7] = (char)(scor / 10 % 10 + '0');
		Litere[i].push_back(new Scoreboard(SirPentruNumere, renderer));
		Litere[i][Litere[i].size() - 1]->init(1240, 200 + (i * 80), 80);

		SirPentruNumere[7] = (char)(scor % 10 + '0');
		Litere[i].push_back(new Scoreboard(SirPentruNumere, renderer));
		Litere[i][Litere[i].size() - 1]->init(1280, 200 + (i * 80), 80);

		SirPentruNumere[7] = (char)(level + '0');
		Litere[i].push_back(new Scoreboard(SirPentruNumere, renderer));
		Litere[i][Litere[i].size() - 1]->init(900, 200 + (i * 80), 80);
	}
}

void Game::InitMainMenu() {
	delete map;
	map = new Map(renderer, 4);
}

void Game::InitLevelsMenu() {
	delete map;
	map = new Map(renderer, 5);
}

void Game::InitHelpMenu() {
	delete map;
	map = new Map(renderer, 6);
}

void Game::InitCreditsMenu() {
	delete map;
	map = new Map(renderer, 7);
}

void Game::InitLoseMenu() {
	delete map;
	map = new Map(renderer, 8);
}

void Game::InitWinMenu() {
	delete map;
	map = new Map(renderer, 9);
}

void Game::InitHallMenu() {
	delete map;
	map = new Map(renderer, 10);
}

void Game::InitLoadOrNewMenu() {
	delete map;
	map = new Map(renderer, 11);
}

void Game::InitLoadMenu() {
	delete map;
	map = new Map(renderer, 12);
}

void Game::InitNewMenu() {
	delete map;
	map = new Map(renderer, 13);
	for (int i = 0; i < 12; i++)
		PlayerNume[i] = 0;
	contorNume = 0;
}

void Game::InitLevel1() {
	delete map;
	delete player;
	delete coin;
	delete live;
	directiex = -1;
	directiey = -1;
	Mix_HaltChannel(-1);
	map = new Map(renderer, 0);
	player = new Player("assets/Nava.png", renderer);
	player->init();
	coin = new Scoreboard("assets/coin.png", renderer);
	coin->init(0, 900, 100);
	live = new Scoreboard("assets/Life.png", renderer);
	live->init(10, 980, 80);

	contorMoney = contorGloante = contorEggs = Iterator = ChickenDown = 0;
	contorMoneyLuati = 0;
	LastLevel = 1;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 15; j++) {
			Chicken[i][j] = new Enemy("assets/Chicken.png", renderer);
			Chicken[i][j]->init((j + 2) * 100, (i * 150) + 250, 110);
		}
	}

	for (int i = 0; i <= 10000; i++) {
		MomentsOfShoot[i].chicken = rand() % 30;
		MomentsOfShoot[i].moment = rand();
	}
}

void Game::InitLevel2() {
	delete map;
	delete player;
	delete coin;
	delete live;
	directiex = -1;
	directiey = -1;
	Mix_HaltChannel(-1);
	map = new Map(renderer, 1);
	player = new Player("assets/Nava.png", renderer);
	player->init();
	coin = new Scoreboard("assets/coin.png", renderer);
	coin->init(0, 900, 100);
	live = new Scoreboard("assets/Life.png", renderer);
	live->init(10, 980, 80);

	contorMoney = contorGloante = contorEggs = Iterator = ChickenDown = 0;
	contorMoneyLuati = 0;
	LastLevel = 2;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 15; j++) {
			delete[]Chicken[i][j];
			Chicken[i][j] = new Enemy("assets/Chicken.png", renderer);
			Chicken[i][j]->init((j + 2) * 100, (i * 150) + 250, 110);
		}
	}

	for (int i = 0; i <= 10000; i++) {
		MomentsOfShoot[i].chicken = rand() % 30;
		MomentsOfShoot[i].moment = rand();
	}
}

void Game::InitLevel3() {
	delete map;
	delete player;
	delete coin;
	delete live;
	directiex = -1;
	directiey = -1;

	Mix_HaltChannel(-1);
	map = new Map(renderer, 2);
	player = new Player("assets/Nava.png", renderer);
	player->init();
	coin = new Scoreboard("assets/coin.png", renderer);
	coin->init(0, 900, 100);
	live = new Scoreboard("assets/Life.png", renderer);
	live->init(10, 980, 80);

	contorMoney = contorGloante = contorEggs = Iterator = ChickenDown = 0;
	contorMoneyLuati = 0;
	LastLevel = 3;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 15; j++) {
			Chicken[i][j] = new Enemy("assets/Chicken.png", renderer);
			Chicken[i][j]->init((j + 2) * 100, (i * 150) + 250, 110);
		}
	}

	for (int i = 0; i <= 10000; i++) {
		MomentsOfShoot[i].chicken = rand() % 30;
		MomentsOfShoot[i].moment = rand();
	}
}

void Game::InitLevel4() {
	delete map;
	delete player;
	delete coin;
	delete live;
	directiex = -1;
	directiey = -1;
	Mix_HaltChannel(-1);
	map = new Map(renderer, 3);
	player = new Player("assets/Nava.png", renderer);
	player->init();
	coin = new Scoreboard("assets/coin.png", renderer);
	coin->init(0, 900, 100);
	live = new Scoreboard("assets/Life.png", renderer);
	live->init(10, 980, 80);

	contorMoney = contorGloante = contorEggs = Iterator = ChickenDown = 0;
	contorMoneyLuati = 0;
	LastLevel = 4;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 15; j++) {
			Chicken[i][j] = new Enemy("assets/Chicken.png", renderer);
			Chicken[i][j]->init((j + 2) * 100, (i * 150) + 250, 110);
		}
	}

	for (int i = 0; i <= 10000; i++) {
		MomentsOfShoot[i].chicken = rand() % 30;
		MomentsOfShoot[i].moment = rand();
	}
}


void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if (WhatModule == 0) ///MainMenu
	{
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (NumberOfLevelsCompleted >= 1)
					File->ImportToFile(PlayerNume, totalScore, NumberOfLevelsCompleted, LevelScore[1], LevelScore[2], LevelScore[3], LevelScore[4], pozFile);
				isRunning = false;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				if (event.button.x >= 710 && event.button.x <= 1210 && event.button.y >= 575 && event.button.y <= 635) {
					if (IfSaveOrNewGame == 0) {
						WhatModule = 11;
						InitLoadOrNewMenu();
					}
					else {
						WhatModule = 1;
						InitLevelsMenu();
					}
				}
				if (event.button.x >= 714 && event.button.x <= 1214 && event.button.y >= 748 && event.button.y <= 808) {
					InitHelpMenu();
					WhatModule = 2;
				}
				if (event.button.x >= 714 && event.button.x <= 1214 && event.button.y >= 833 && event.button.y <= 893) {
					InitCreditsMenu();
					WhatModule = 3;
				}
				if(event.button.x >= 709 && event.button.x <= 1209 && event.button.y >= 663 && event.button.y <= 723) {
					InitHallMenu();
					WhatModule = 10;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	if (WhatModule == 1) { ///LevelMenu
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				InitMainMenu();
				WhatModule = 0;
				break;
			default:
				break;
			}
		break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				if (event.button.x >= 228 && event.button.x <= 437 && event.button.y >= 689 && event.button.y <= 898) {
					InitLevel1();
					WhatModule = 6;
				}
				if (event.button.x >= 604 && event.button.x <= 813 && event.button.y >= 540 && event.button.y <= 749) {
					if (NumberOfLevelsCompleted >= 1) {
						InitLevel2();
						WhatModule = 7;
					}
				}
				if (event.button.x >= 922 && event.button.x <= 1131 && event.button.y >= 392 && event.button.y <= 601) {
					if (NumberOfLevelsCompleted >= 2) {
						InitLevel3();
						WhatModule = 8;
					}
				}
				if (event.button.x >= 1261 && event.button.x <= 1470 && event.button.y >= 248 && event.button.y <= 457) {
					if (NumberOfLevelsCompleted >= 3) {
						InitLevel4();
						WhatModule = 9;
					}
				}
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	if (WhatModule == 2) { //HelpMenu
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				InitMainMenu();
				WhatModule = 0;
				break;
			default:
				break;
			}
		}
	}

	if (WhatModule == 3) {//CreditsMenu
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				InitMainMenu();
				WhatModule = 0;
				break;
			default:
				break;
			}
		}
	}

	if (WhatModule == 4) { //LoseMenu
		switch (event.type)
		{
			case SDL_QUIT: {
				isRunning = false;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
				case SDL_BUTTON_LEFT:
					if (event.button.x >= 94 && event.button.x <= 794 && event.button.y >= 529 && event.button.y <= 613) {
						switch (LastLevel) {
							case 1:
								InitLevel1();
								break;
							case 2:
								InitLevel2();
								break;
							case 3:
								InitLevel3();
								break;
							case 4:
								InitLevel4();
								break;
							default:
								break;
						}
						WhatModule = 6;
					}
					if (event.button.x >= 1133 && event.button.x <= 1833 && event.button.y >= 529 && event.button.y <= 613) {
						InitLevelsMenu();
						WhatModule = 1;
						Mix_PlayChannel(-1, BackMusicMenu, 1000);
					}
					break;
				default:
					break;
				}

		}
	}

	if (WhatModule == 5) { //WinMenu
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				if (event.button.x >= 94 && event.button.x <= 794 && event.button.y >= 529 && event.button.y <= 613) {
					switch (LastLevel) {
					case 1:
						InitLevel1();
						break;
					case 2:
						InitLevel2();
						break;
					case 3:
						InitLevel3();
						break;
					case 4:
						InitLevel4();
						break;
					default:
						break;
					}
					WhatModule = 6;
				}
				if (event.button.x >= 1133 && event.button.x <= 1833 && event.button.y >= 529 && event.button.y <= 613) {
					InitLevelsMenu();
					WhatModule = 1;
					Mix_PlayChannel(-1, BackMusicMenu, 1000);
				}
			default:
				break;
			}

		}
	}

	if (WhatModule == 10) { //HallofFame
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				InitMainMenu();
				WhatModule = 0;
				break;
			default:
				break;
			}
		}
	}

	if (WhatModule == 11) { ///LoadOrNew
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				InitMainMenu();
				WhatModule = 0;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				if (event.button.x >= 710 && event.button.x <= 1210 && event.button.y >= 628 && event.button.y <= 688) {
					InitLoadMenu();
					WhatModule = 12;
					IfSaveOrNewGame = 1;
				}
				if (event.button.x >= 710 && event.button.x <= 1210 && event.button.y >= 350 && event.button.y <= 410) {
					InitNewMenu();
					WhatModule = 13;
					IfSaveOrNewGame = 2;
				}
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	if (WhatModule == 12) {//LoadMenu
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				InitLoadOrNewMenu();
				WhatModule = 11;
				IfSaveOrNewGame = 0;
				break;
			case SDLK_0:
				if (Numbers > 0) {
					pozFile = 0;
					strcpy(PlayerNume, File->ExportNume(0));
					NumberOfLevelsCompleted = File->ExportLevel(0);
					totalScore = File->ExportScore(0);
					LevelScore[0] = File->ExportL1(0);
					LevelScore[1] = File->ExportL2(0);
					LevelScore[2] = File->ExportL3(0);
					LevelScore[3] = File->ExportL4(0);
					InitLevelsMenu();
					WhatModule = 1;
				}
			break;
			case SDLK_1:
				if (Numbers > 1) {
					pozFile = 1;
					strcpy(PlayerNume, File->ExportNume(1));
					NumberOfLevelsCompleted = File->ExportLevel(1);
					totalScore = File->ExportScore(1);
					LevelScore[0] = File->ExportL1(1);
					LevelScore[1] = File->ExportL2(1);
					LevelScore[2] = File->ExportL3(1);
					LevelScore[3] = File->ExportL4(1);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_2:
				if (Numbers > 2) {
					pozFile = 2;
					strcpy(PlayerNume, File->ExportNume(2));
					NumberOfLevelsCompleted = File->ExportLevel(2);
					totalScore = File->ExportScore(2);
					LevelScore[0] = File->ExportL1(2);
					LevelScore[1] = File->ExportL2(2);
					LevelScore[2] = File->ExportL3(2);
					LevelScore[3] = File->ExportL4(2);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_3:
				if (Numbers > 3) {
					pozFile = 3;
					strcpy(PlayerNume, File->ExportNume(3));
					NumberOfLevelsCompleted = File->ExportLevel(3);
					totalScore = File->ExportScore(3);
					LevelScore[0] = File->ExportL1(3);
					LevelScore[1] = File->ExportL2(3);
					LevelScore[2] = File->ExportL3(3);
					LevelScore[3] = File->ExportL4(3);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_4:
				if (Numbers > 4) {
					pozFile = 4;
					strcpy(PlayerNume, File->ExportNume(4));
					NumberOfLevelsCompleted = File->ExportLevel(4);
					totalScore = File->ExportScore(4);
					LevelScore[0] = File->ExportL1(4);
					LevelScore[1] = File->ExportL2(4);
					LevelScore[2] = File->ExportL3(4);
					LevelScore[3] = File->ExportL4(4);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_5:
				if (Numbers > 5) {
					pozFile = 5;
					strcpy(PlayerNume, File->ExportNume(5));
					NumberOfLevelsCompleted = File->ExportLevel(5);
					totalScore = File->ExportScore(5);
					LevelScore[0] = File->ExportL1(5);
					LevelScore[1] = File->ExportL2(5);
					LevelScore[2] = File->ExportL3(5);
					LevelScore[3] = File->ExportL4(5);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_6:
				if (Numbers > 6) {
					pozFile = 6;
					strcpy(PlayerNume, File->ExportNume(6));
					NumberOfLevelsCompleted = File->ExportLevel(6);
					totalScore = File->ExportScore(6);
					LevelScore[0] = File->ExportL1(6);
					LevelScore[1] = File->ExportL2(6);
					LevelScore[2] = File->ExportL3(6);
					LevelScore[3] = File->ExportL4(6);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_7:
				if (Numbers > 7) {
					pozFile = 7;
					strcpy(PlayerNume, File->ExportNume(7));
					NumberOfLevelsCompleted = File->ExportLevel(7);
					totalScore = File->ExportScore(7);
					LevelScore[0] = File->ExportL1(7);
					LevelScore[1] = File->ExportL2(7);
					LevelScore[2] = File->ExportL3(7);
					LevelScore[3] = File->ExportL4(7);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_8:
				if (Numbers > 8) {
					pozFile = 8;
					strcpy(PlayerNume, File->ExportNume(8));
					NumberOfLevelsCompleted = File->ExportLevel(8);
					totalScore = File->ExportScore(8);
					LevelScore[0] = File->ExportL1(8);
					LevelScore[1] = File->ExportL2(8);
					LevelScore[2] = File->ExportL3(8);
					LevelScore[3] = File->ExportL4(8);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			case SDLK_9:
				if (Numbers > 9) {
					pozFile = 9;
					strcpy(PlayerNume, File->ExportNume(9));
					NumberOfLevelsCompleted = File->ExportLevel(9);
					totalScore = File->ExportScore(9);
					LevelScore[0] = File->ExportL1(9);
					LevelScore[1] = File->ExportL2(9);
					LevelScore[2] = File->ExportL3(9);
					LevelScore[3] = File->ExportL4(9);
					InitLevelsMenu();
					WhatModule = 1;
				}
				break;
			default:
				break;
			}
		}
	}
	
	if (WhatModule == 13) {//NewMenu
		switch (event.type)
		{
		case SDL_QUIT: {
			isRunning = false;
			break;
		}
		case SDL_TEXTINPUT:
			if (contorNume < 10) {
				strcat(PlayerNume, event.text.text);
				contorNume++;
				SirPentruLitere[12] = PlayerNume[contorNume - 1];
				NumePlayerLitere.push_back(new Scoreboard(SirPentruLitere, renderer));
				NumePlayerLitere[contorNume - 1]->init(610 + (contorNume * 70), 620, 60);
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_BACKSPACE:
				if (contorNume > 0) {
					contorNume--;
					PlayerNume[contorNume] = 0;
					NumePlayerLitere.pop_back();
				}
			break;
			case SDLK_ESCAPE:
				InitLoadOrNewMenu();
				WhatModule = 11;
				IfSaveOrNewGame = 0;
				break;
			case SDLK_RETURN:
				InitLevelsMenu();
				WhatModule = 1;
				break;
			default:
				break;
			}
		}
	}

	if (WhatModule >= 6 && WhatModule < 10) ///Levels
	{
		if (player->GetLifes() <= 0) {
			Mix_PlayChannel(1, ExplosionNava, 0);
			InitLoseMenu();
			WhatModule = 4;
		}
		else
			if (ChickenDown == 30 && contorMoneyLuati == 30) {
				Mix_PlayChannel(-1, WOW, 0);
				InitWinMenu();
				WhatModule = 5;

				int MoneyCnt = player->GetMoney();
				if (LevelScore[LastLevel] < MoneyCnt) {
					totalScore = totalScore - LevelScore[LastLevel] + MoneyCnt;
					LevelScore[LastLevel] = MoneyCnt;
				}

				if (LastLevel > NumberOfLevelsCompleted) {
					NumberOfLevelsCompleted = LastLevel;
				}
			}
		else {

			switch (event.type)
			{
			case SDL_QUIT: {
				isRunning = false;
				break;
			}
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					InitLevelsMenu();
					WhatModule = 1;
					Mix_PlayChannel(-1, BackMusicMenu, 1000);
					break;
				case SDLK_SPACE:
					SDL_Rect curent = player->GetCurentPosition();
					Glont[++contorGloante] = new Bullet("assets/NavaGlont.png", renderer);
					Glont[contorGloante]->init(curent.x + 35, curent.y - 20, 80);
					Mix_PlayChannel(0, ShotNava, 0);
					break;
				case SDLK_w:
					player->update(1);
					break;
				case SDLK_s:
					player->update(2);
					break;
				case SDLK_a:
					player->update(3);
					break;
				case SDLK_d:
					player->update(4);
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
			default:
				break;
			}
		}
	}
}

inline bool VeziDacaEAcolo(SDL_Rect A, SDL_Rect B, int distance = 110) {
	return ((A.x >= B.x) && (A.x <= (B.x + distance)) && (A.y >= B.y) && (A.y <= (B.y + distance)));
}

bool Lovitura(SDL_Rect curentGlont, int i) {
	SDL_Rect curentPasare;

	for (int j = 1; j >= 0; j--) {
		for (int k = 14; k >= 0; k--) {
			if (Chicken[j][k] != nullptr) {
				curentPasare = Chicken[j][k]->GetPosition();
				if (VeziDacaEAcolo(curentGlont, curentPasare))
				{
					delete[] Chicken[j][k];
					Chicken[j][k] = nullptr;
					return 1;
				}
			}
		}
	}
	return 0;
}

void CreateMoney(SDL_Rect A, SDL_Renderer* renderer) {
	Money[++contorMoney] = new Bullet("assets/coin.png", renderer);
	Money[contorMoney]->init(A.x, A.y, 110);
}


void Game::update() const
{
	if ((WhatModule >= 0 && WhatModule <= 5) || WhatModule >= 10){

	}
	else {
		Iterator++;
		player->update();
		coin->update();
		live->update();
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 15; j++) {
				if (Chicken[i][j] != nullptr)
					Chicken[i][j]->update(LastLevel);
			}
		}

		//"a dat ala cu viteza", citat mare filosof in viata! 
		bool amlovit = 0;
		SDL_Rect curentGlont;
		for (int i = 1; i <= contorGloante; i++)
			if (Glont[i] != nullptr)
			{
				Glont[i]->update();
				curentGlont = Glont[i]->GetPosition();
				amlovit = 0;

				amlovit = Lovitura(curentGlont, i);

				if (curentGlont.y < 0) {
					delete[]Glont[i];
					Glont[i] = nullptr;
				}
				if (amlovit == 1) {
					CreateMoney(curentGlont, renderer);
					ChickenDown++;
					delete[]Glont[i];
					Glont[i] = nullptr;
					Mix_PlayChannel(2, ChickenHurt, 0);
				}
			}

		//Ma imbogatesc sa moara mama
		SDL_Rect playerCurent, curentBanut;
		playerCurent = player->GetCurentPosition();
		for (int i = 1; i <= contorMoney; i++) {
			if (Money[i] != nullptr) {
				Money[i]->update(1);
				curentBanut = Money[i]->GetPosition();
				if (VeziDacaEAcolo(curentBanut, playerCurent)) {
					Mix_PlayChannel(-1, CoinSound, 0);
					contorMoneyLuati++;
					player->IncreaseMoney();
					delete[]Money[i];
					Money[i] = nullptr;
				}
				else
					if (curentBanut.y > 1080) {
						contorMoneyLuati++;
						delete[]Money[i];
						Money[i] = nullptr;
					}
			}
		}

		//mare scoreboard
		int MoneyCurent = player->GetMoney();
		int Liveunitati = player->GetLifes();
		int ScoreUnitati = MoneyCurent % 10;
		int ScoreZeci = MoneyCurent / 10 % 10;

		delete coinunitati;
		delete coinzeci;
		delete liveunitati;
		SirPentruNumere[7] = (char)(ScoreUnitati + '0');
		coinunitati = new Scoreboard(SirPentruNumere, renderer);
		coinunitati->init(130, 910, 80);

		SirPentruNumere[7] = (char)(ScoreZeci + '0');
		coinzeci = new Scoreboard(SirPentruNumere, renderer);
		coinzeci->init(100, 910, 80);

		SirPentruNumere[7] = (char)(Liveunitati + '0');
		liveunitati = new Scoreboard(SirPentruNumere, renderer);
		liveunitati->init(100, 990, 80);

		//oua magice
		SDL_Rect curentChicken;
		int xChicken, yChicken;
		for (int i = 0; i <= 1000; i++) {
			if (Iterator == MomentsOfShoot[i].moment) {
				xChicken = MomentsOfShoot[i].chicken / 15;
				yChicken = MomentsOfShoot[i].chicken % 15;
				if (Chicken[xChicken][yChicken] != nullptr) {
					curentChicken = Chicken[xChicken][yChicken]->GetPosition();
					Eggs[++contorEggs] = new Bullet("assets/EGG1.png", renderer);
					Eggs[contorEggs]->init(curentChicken.x - 30, curentChicken.y + 30, 80);
				}
			}
		}

		SDL_Rect curentEgg;
		for (int i = 1; i <= contorEggs; i++) {
			if (Eggs[i] != nullptr) {
				Eggs[i]->update(1);
				curentEgg = Eggs[i]->GetPosition();
				if (curentEgg.y > 1080) {
					delete[]Eggs[i];
					Eggs[i] = nullptr;
				}
				if (VeziDacaEAcolo(curentEgg, playerCurent, 80)) {
					player->DecreaseLifes();
					delete[]Eggs[i];
					Eggs[i] = nullptr;
				}
			}
			if (player->GetLifes() <= 0)
				return;
		}
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	if ((WhatModule >= 0 && WhatModule <= 5) || WhatModule >= 10) {
		map->DrawMap();
		if (WhatModule == 10 || WhatModule == 12) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < Litere[i].size(); j++) {
					Litere[i][j]->draw();
				}
			}
		}
		if (WhatModule == 13) {
			for (auto w : NumePlayerLitere) {
				w->draw();
			}
		}
	}

	else {
		map->DrawMap();
		// this is where we would add stuff to render
		player->draw();

		live->draw();
		coin->draw();
		coinunitati->draw();
		liveunitati->draw();
		coinzeci->draw();

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 15; j++) {
				if (Chicken[i][j] != nullptr)
					Chicken[i][j]->draw();
			}
		}


		for (int i = 1; i <= contorGloante; i++) {
			if (Glont[i] != nullptr)
				Glont[i]->draw();
		}

		for (int i = 1; i <= contorMoney; i++) {
			if (Money[i] != nullptr)
				Money[i]->draw();
		}

		for (int i = 1; i <= contorEggs; i++) {
			if (Eggs[i] != nullptr) {
				Eggs[i]->draw();
			}
		}

	}
	SDL_RenderPresent(renderer);
}

void Game::clean() const
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}