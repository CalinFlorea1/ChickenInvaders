#pragma once
#include <SDL_image.h>

class Map
{
public:
	Map(SDL_Renderer* renderer, int position);
	~Map();

	void LoadMap(int arr[1][1]);
	void DrawMap();

private:
	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* L1; //0
	SDL_Texture* L2; //1
	SDL_Texture* L3; //2
	SDL_Texture* L4; //3
	SDL_Texture* Main; //4
	SDL_Texture* Levels; //5
	SDL_Texture* Help; //6
	SDL_Texture* Credits; //7
	SDL_Texture* Lose; //8
	SDL_Texture* Win; //9
	SDL_Texture* Hall;//10
	SDL_Texture* LoadOrNew;//11
	SDL_Texture* Load;//12
	SDL_Texture* New;//13
	
	int map[1][1];

};