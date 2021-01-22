#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
}

void Enemy::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Enemy::init(int inaltime, int lungime, int marime)
{
	srcRect.x = srcRect.y = 0;
	destRect.x = inaltime;
	destRect.y = lungime;
	srcRect.w = srcRect.h = marime;
	destRect.w = destRect.h = marime;
}

int directiex, directiey;
void Enemy::update(int direction)
{
	switch (direction) {
		case 1:
			if (directiex == -1)
				if (destRect.x < 110)
					directiex = 1;
				
			if (directiex == 1)
				if (destRect.x > 1700)
					directiex = -1;
			destRect.x = destRect.x + directiex;
			break;
		case 2:
			if (directiex == -1 && directiey == 0) 
				if (destRect.x < 110) {
					directiex = -1;
					directiey = -1;
				}
			if (directiex == -1 && directiey == -1)
				if (destRect.y < 110 || destRect.x < 0) {
					directiex = 1;
					directiey = 0;
				}
			if (directiex == 1 && directiey == 0) {
				if (destRect.x > 1800) {
					directiex = -1;
					directiey = 1;
				}
			}
			if (directiex == -1 && directiey == 1){
				if (destRect.y > 500) {
					directiex = -1;
					directiey = 0;
				}

			}
			destRect.x = destRect.x + directiex;
			destRect.y = destRect.y + directiey;
			break;
		case 3:
			if (directiex == -1 && directiey == -1) {
				if (destRect.x < 0) {
					directiex = 1;
					directiey = -1;
				}
				if (destRect.y < 200) {
					directiex = -1;
					directiey = 1;
				}
			}
			if (directiex == -1 && directiey == 1) {
				if (destRect.x < 0) {
					directiex = 1;
					directiey = -1;
				}
				if (destRect.y > 600) {
					directiex = -1;
					directiey = -1;
				}
			}
			if (directiex == 1 && directiey == -1) {
				if (destRect.x > 1800) {
					directiex = -1;
					directiey = 1;
				}
				if (destRect.y < 200) {
					directiex = 1;
					directiey = 1;
				}
			}

			if (directiex == 1 && directiey == 1) {
				if (destRect.x > 1800) {
					directiex = -1;
					directiey = -1;
				}
				if (destRect.y > 700) {
					directiex = -1;
					directiey = 1;
				}
			}
			destRect.x = destRect.x + directiex;
			destRect.y = destRect.y + directiey;
			break;
		case 4:
			if (directiex == -1 && directiey == -1) { ///stanga sus
				if (destRect.x < 0) {
					directiex = 0;
					directiey = 1;
				}
				if (destRect.y < 80){
					directiex = 1;
					directiey = 0;
				}
			}
			if (directiex == 1 && directiey == 0) { ///dreapta
				if (destRect.x > 1800) {
					directiex = -1;
					directiey = 1;
				}
			}

			if (directiex == -1 && directiey == 1) { ///stanga jos
				if (destRect.y > 500) {
					directiex = -1;
					directiey = -1;
				}
				if (destRect.x < 100) {
					directiex = 1;
					directiey = -1;
				}
			}

			if (directiex == 1 && directiey == -1) { ///dreaptasus
				if (destRect.y < 140) {
					directiex = 1;
					directiey = 0;
				}
				if (destRect.x > 1800) {
					directiex = -1;
					directiey = 1;
				}
			}

			if (directiex == 0 && directiey == 1) {
				if (destRect.y > 600) {
					directiex = 1;
					directiey = -1;
				}
			}
			destRect.x = destRect.x + directiex;
			destRect.y = destRect.y + directiey;
			break;
		default:
			break;
	}
}

SDL_Rect Enemy::GetPosition() {
	return destRect;
}

void Enemy::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}

Enemy :: ~Enemy() {
	SDL_DestroyTexture(texture);
}