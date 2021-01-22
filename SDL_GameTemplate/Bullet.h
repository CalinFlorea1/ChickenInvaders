#pragma once
#include "Component.h"
#include "SDL.h"

class Bullet : public Component
{
	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};

public:
	Bullet() = default;
	Bullet(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init(int inaltime = 900, int lungime = 900, int marime = 150) override;

	void update(int direction = 0) override;

	void draw() override;

	SDL_Rect GetPosition();
	~Bullet();
};
