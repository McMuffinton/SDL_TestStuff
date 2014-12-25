#include "Sprite.h"

Sprite::Sprite(string imagePath, int src_x, int src_y, int src_width, int src_height){
	init(imagePath, src_x, src_y, src_width, src_height);
}

Sprite::~Sprite(){
	SDL_FreeSurface(spriteSheet);
}

void Sprite::init(string imagePath, int src_x, int src_y, int src_width, int src_height){
	spriteSheet = SDL_LoadBMP(imagePath.c_str());
	if (spriteSheet == NULL){
		printf("Something went terribly wrong: %s\n", SDL_GetError());
	}
	spriteRect.x = src_x;
	spriteRect.y = src_y;
	spriteRect.w = src_width;
	spriteRect.h = src_height;
}

void Sprite::draw(SDL_Surface* windowSurface, int x, int y){
	SDL_Rect screenPosRect;
	screenPosRect.x = x;
	screenPosRect.y = y;

	SDL_BlitSurface(spriteSheet, &spriteRect, windowSurface, &screenPosRect);
}