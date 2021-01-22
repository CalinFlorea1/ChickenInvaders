#include "Map.h"
#include "TextureManager.h"
#include <SDL.h>

int LVL1[1][1] = {
		{0}
};
int LVL2[1][1] = {
		{1}
};
int LVL3[1][1] = {
		{2}
};
int LVL4[1][1] = {
		{3}
};
int MainMenu[1][1] = {
	{4}
};
int LevelsMenu[1][1] = {
	{5}
};
int HelpMenu[1][1] = {
	{6}
};
int CreditsMenu[1][1] = {
	{7}
};
int LoseMenu[1][1] = {
	{8}
};
int WinMenu[1][1] = {
	{9}
};
int HallMenu[1][1] = {
	{10}
};
int LoadOrNewMenu[1][1] = {
	{11}
};
int LoadMenu[1][1] = {
	{12}
};
int NewMenu[1][1] = {
	{13}
};


Map::Map(SDL_Renderer* renderer, int position)
{
	this->renderer = renderer;
	L1 = TextureManager::LoadTexture("assets/Back1.png", renderer);
	L2 = TextureManager::LoadTexture("assets/Back2.png", renderer);
	L3 = TextureManager::LoadTexture("assets/Back3.png", renderer);
	L4 = TextureManager::LoadTexture("assets/Back4.png", renderer);
	Main = TextureManager::LoadTexture("assets/MainMenu.png", renderer);
	Levels = TextureManager::LoadTexture("assets/Levels.png", renderer);
	Help = TextureManager::LoadTexture("assets/Help.png", renderer);
	Credits = TextureManager::LoadTexture("assets/Credits.png", renderer);
	Lose = TextureManager::LoadTexture("assets/LoseMenu.png", renderer);
	Win = TextureManager::LoadTexture("assets/WinMenu.png", renderer);
	Hall = TextureManager::LoadTexture("assets/Hall.png", renderer);
	LoadOrNew = TextureManager::LoadTexture("assets/SAVE.png", renderer);
	Load = TextureManager::LoadTexture("assets/LoadGame.png", renderer);
	New = TextureManager::LoadTexture("assets/TypeTextMenu.png", renderer);
	

	switch (position) {
		case 0:
			LoadMap(LVL1);
			break;
		case 1:
			LoadMap(LVL2);
			break;
		case 2:
			LoadMap(LVL3);
			break;
		case 3:
			LoadMap(LVL4);
			break;
		case 4:
			LoadMap(MainMenu);
			break;
		case 5:
			LoadMap(LevelsMenu);
			break;
		case 6:
			LoadMap(HelpMenu);
			break;
		case 7:
			LoadMap(CreditsMenu);
			break;
		case 8:
			LoadMap(LoseMenu);
			break;
		case 9:
			LoadMap(WinMenu);
			break;
		case 10:
			LoadMap(HallMenu);
			break;
		case 11:
			LoadMap(LoadOrNewMenu);
			break;
		case 12:
			LoadMap(LoadMenu);
			break;
		case 13:
			LoadMap(NewMenu);
			break;
		default:
			break;
	}

	src.x = 0;
	src.y = 0;
	src.w = 1920;
	src.h = 1080;
	dest.x = 0;
	dest.y = 0;
	dest.w = 1920;
	dest.h = 1080;

}

void Map::LoadMap(int arr[1][1])
{
	for (int row = 0; row < 1; row++)
	{
		for (int column = 0; column < 1; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 1; row++)
	{
		for (int column = 0; column < 1; column++)
		{
			type = map[row][column];

			dest.x = column * 60;
			dest.y = row * 60;
			switch (type)
			{
			case 0:
				TextureManager::Draw(L1, src, dest, renderer);
				break;
			case 1:
				TextureManager::Draw(L2, src, dest, renderer);
				break;
			case 2:
				TextureManager::Draw(L3, src, dest, renderer);
				break;
			case 3:
				TextureManager::Draw(L4, src, dest, renderer);
				break;
			case 4:
				TextureManager::Draw(Main, src, dest, renderer);
				break;
			case 5:
				TextureManager::Draw(Levels, src, dest, renderer);
				break;
			case 6:
				TextureManager::Draw(Help, src, dest, renderer);
				break;
			case 7:
				TextureManager::Draw(Credits, src, dest, renderer);
				break;
			case 8:
				TextureManager::Draw(Lose, src, dest, renderer);
				break;
			case 9:
				TextureManager::Draw(Win, src, dest, renderer);
				break;
			case 10:
				TextureManager::Draw(Hall, src, dest, renderer);
				break;
			case 11:
				TextureManager::Draw(LoadOrNew, src, dest, renderer);
				break;
			case 12:
				TextureManager::Draw(Load, src, dest, renderer);
				break;
			case 13:
				TextureManager::Draw(New, src, dest, renderer);
				break;
			default:
				break;
			}
		}
	}
}

Map :: ~Map() {
	SDL_DestroyTexture(L1);
	SDL_DestroyTexture(L2);
	SDL_DestroyTexture(L3);
	SDL_DestroyTexture(L4);
	SDL_DestroyTexture(Main);
	SDL_DestroyTexture(Levels);
	SDL_DestroyTexture(Help);
	SDL_DestroyTexture(Credits);
	SDL_DestroyTexture(Lose);
	SDL_DestroyTexture(Win);
	SDL_DestroyTexture(Hall);
	SDL_DestroyTexture(LoadOrNew);
	SDL_DestroyTexture(Load);
	SDL_DestroyTexture(New);

}