#include "Scoreboard.h"
#include "TextureManager.h"

Scoreboard::Scoreboard(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
}

void Scoreboard::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Scoreboard::init(int inaltime, int lungime, int marime)
{
	srcRect.x = srcRect.y = 0;
	destRect.x = inaltime;
	destRect.y = lungime;
	srcRect.w = srcRect.h = marime;
	destRect.w = destRect.h = marime;
}

void Scoreboard::update(int direction)
{
	;
}


void Scoreboard::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}

Scoreboard :: ~Scoreboard() {
	SDL_DestroyTexture(texture);
}