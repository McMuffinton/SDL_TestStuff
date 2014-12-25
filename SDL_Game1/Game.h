#include <stdio.h>
#include <SDL.h>
#include "Sprite.h"
#include "Keyboard.h"

class Game{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	Keyboard keyboard;

	bool running = true;

public:
	Game();
	~Game();

	bool init();
	void run();
	void handleInput(SDL_Event *event);
	void update();
	void draw();
	void cleanup();
};