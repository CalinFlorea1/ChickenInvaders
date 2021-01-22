#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	setTex(path);
}

void Bullet::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Bullet::init(int inaltime, int lungime, int marime)
{
	srcRect.x = srcRect.y = 0;
	destRect.x = inaltime;
	destRect.y = lungime;
	srcRect.w = srcRect.h = marime;
	destRect.w = destRect.h = marime;
}

void Bullet::update(int direction)
{
	/// direction = 0 -> glont de la nava altfel este ou de la pasare
	switch (direction) {
		case 0:
			destRect.y -= 10;
			break;
		case 1:
			destRect.y += 3;
			break;
		default:
			break;
	}
}


void Bullet::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer);
}


SDL_Rect Bullet::GetPosition() {
	return destRect;
}

Bullet :: ~Bullet() {
	SDL_DestroyTexture(texture);
}