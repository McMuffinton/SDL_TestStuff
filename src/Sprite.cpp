#include "Sprite.h"

Sprite::Sprite(string imagePath, int src_x, int src_y, int src_width, int src_height) {
    this->spriteSheet = SDL_LoadBMP(imagePath.c_str());
    if(spriteSheet == NULL) {
        printf("Something went terribly wrong: %s\n", SDL_GetError());
    }
    this->spriteRect.x = src_x;
    this->spriteRect.y = src_y;
    this->spriteRect.w = src_width;
    this->spriteRect.h = src_height;
}

Sprite::Sprite(string imagePath, uint8_t R, uint8_t G, uint8_t B, int src_x, int src_y, int src_width, int src_height) {
    this->spriteSheet = SDL_LoadBMP(imagePath.c_str());
    if(spriteSheet == NULL) {
        printf("Something went terribly wrong: %s\n", SDL_GetError());
    }
    SDL_SetColorKey(spriteSheet, 1, SDL_MapRGB(spriteSheet->format, R, G, B));
    this->spriteRect.x = src_x;
    this->spriteRect.y = src_y;
    this->spriteRect.w = src_width;
    this->spriteRect.h = src_height;
}

Sprite::~Sprite() {
    SDL_FreeSurface(this->spriteSheet);
}

void Sprite::draw(SDL_Surface* windowSurface, int x, int y) {
    SDL_Rect screenPosRect;
    screenPosRect.x = x;
    screenPosRect.y = y;

    SDL_BlitSurface(this->spriteSheet, &this->spriteRect, windowSurface, &screenPosRect);
}