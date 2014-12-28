#include "animatedSprite.h"

animatedSprite::animatedSprite(
	string imagePath,
	uint8_t R, uint8_t G, uint8_t B,
	int src_x, int src_y,
	int src_width, int src_height,
	int totalSprites, int framesPerSprite[]) :
		Sprite(
			imagePath,
			R,  G,  B,
			src_x,  src_y,
			src_width, src_height){

	this->totalSprites = totalSprites;
	this->stepWidth = src_width;
	//Stuff the framesPerSprite information in a vector array
	for (int i = 0; i < totalSprites; i++){
		this->framesPerSprite.push_back(framesPerSprite[i]);
	}
}

animatedSprite::~animatedSprite(){
	SDL_FreeSurface(this->spriteSheet);
}

void animatedSprite::update(){
	//If we're supposed to change into the next frame of animation
	if (this->framesSinceLastUpdate == framesPerSprite[this->currentSprite]){
		this->currentSprite++;
		this->framesSinceLastUpdate = 0;
		//If we're out of the bounds of our animation
		if (this->currentSprite == this->totalSprites){
			this->currentSprite = 0;
			this->spriteRect.x -= this->stepWidth * (totalSprites - 1);
		} else {
			this->spriteRect.x += this->stepWidth;
		}
	}
	framesSinceLastUpdate++;
}