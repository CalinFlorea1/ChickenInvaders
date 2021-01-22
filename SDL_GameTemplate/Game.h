#pragma once
#include <SDL.h>


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void InitMainMenu();
	void InitLevel1();
	void InitLevel2();
	void InitLevel3();
	void InitLevel4();
	void InitLevelsMenu();
	void InitHelpMenu();
	void InitCreditsMenu();
	void InitLoseMenu();
	void InitHallMenu();
	void InitWinMenu();
	void InitLoadOrNewMenu();
	void InitLoadMenu();
	void InitNewMenu();
	
	void FilesEntries();

	void handleEvents();
	void update() const;
	void render() const;
	void clean() const;

	bool running() const { return isRunning;  }
private:
	bool isRunning;
	int WhatModule;
	SDL_Window* window;
	SDL_Renderer* renderer;
};
