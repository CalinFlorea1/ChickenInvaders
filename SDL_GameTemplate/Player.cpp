#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* path, SDL_Renderer* renderer): renderer(renderer)
{
   setTex(path);
}

void Player::setTex(const char* path)
{
   texture = TextureManager::LoadTexture(path, renderer);
}

void Player::init(int inaltime, int lungime, int marime)
{
	Life = 3;
	Score = 0;
	srcRect.x = srcRect.y = 0;
	destRect.x = inaltime;
	destRect.y = lungime;
	srcRect.w = srcRect.h = marime;
	destRect.w = destRect.h = marime;
}

void Player::update(int direction)
{
	switch (direction) {
	case 1:
		if (destRect.y > 0)
			destRect.y -= 20;
		break;
	case 2:
		if (destRect.y < 930)
			destRect.y += 20;
		break;
	case 3:
		if (destRect.x > 0)
			destRect.x -= 20;
		break;
	case 4:
		if (destRect.x < 1800)
			destRect.x += 20;
		break;
	default:
		break;
	}
}


void Player::draw()
{
   TextureManager::Draw(texture, srcRect, destRect, renderer);
}

SDL_Rect Player::GetCurentPosition() {
	return destRect;
}

void Player::IncreaseMoney() {
	Score++;
}

void Player::DecreaseLifes() {
	Life--;
}

int Player::GetMoney() {
	return Score;
}

int& Player::GetLifes() {
	return Life;
}

Player :: ~Player() {
	SDL_DestroyTexture(texture);
}