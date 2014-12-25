#include <stdio.h>
#include <string>
#include <SDL.h>

using namespace std;

class Sprite{
	SDL_Surface* spriteSheet;
	SDL_Rect spriteRect;

	public:
		Sprite(string imagePath,
			int src_x,
			int src_y,
			int src_width,
			int src_height);

		~Sprite();

		void init(string imagePath, int src_x, int src_y, int src_width, int src_height);
		void draw(SDL_Surface* windowSurface, int x, int y);
};