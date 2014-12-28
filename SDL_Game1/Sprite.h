#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <inttypes.h>
#include <string>
#include <SDL.h>

using namespace std;

class Sprite{
protected:
	SDL_Surface* spriteSheet;
	SDL_Rect spriteRect;

	public:
		Sprite(string imagePath,
			uint8_t R, uint8_t G, uint8_t B,
			int src_x, int src_y,
			int src_width, int src_height);

		Sprite(string imagePath,
			int src_x, int src_y,
			int src_width, int src_height);

		~Sprite();

		void draw(SDL_Surface* windowSurface, int x, int y);
};

#endif