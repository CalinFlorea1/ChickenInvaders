#pragma once
#include "Enemy.h"
#include "SDL.h"

class Player : public Enemy
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};
	int Life;
	int Score;

public:
   Player() = default;
   Player(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init(int inaltime = 900, int lungime = 900, int marime = 150) override;

	void update(int direction = 0) override;

	void draw() override;

	void IncreaseMoney();

	void DecreaseLifes();

	int &GetLifes();

	int GetMoney();

	SDL_Rect GetCurentPosition();

	~Player();
};
