#pragma once
#include "Component.h"
#include "SDL.h"

class Scoreboard : public Component {

	SDL_Texture* texture{};
	SDL_Renderer* renderer{};
	SDL_Rect srcRect{}, destRect{};

public:
	Scoreboard() = default;
	Scoreboard(const char* path, SDL_Renderer * renderer);

	void setTex(const char* path);

	void init(int inaltime = 900, int lungime = 900, int marime = 150) override;

	void update(int direction = 0) override;

	void draw() override;

	~Scoreboard();
};
