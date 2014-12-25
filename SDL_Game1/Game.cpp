#include "Game.h"

Game::Game(){
	if (!init()){
		printf("Couldn't create the game\n");
	} else {
		run();
	}
}

Game::~Game(){
	cleanup();
}

bool Game::init(){
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING < 0)){
		printf("Something went wrong while initting: %s\n", SDL_GetError());
		success = false;
	} else {
		window = SDL_CreateWindow("Vidya gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL){
			printf("Something went wrong while making a window! : %s\n", SDL_GetError());
			success = false;
		} else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return success;
}

int x = 0, y = 0;
Sprite lole("res/img/stuff.bmp", 0, 0, 32, 32);

void Game::run(){
	while (running){
		int startTime = SDL_GetTicks();
		
		update();

		draw();

		int timeSpent = startTime - SDL_GetTicks();

		SDL_Delay((1000 / 60) - timeSpent);
	}
}

void Game::update(){
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0){
		handleInput(&event);
	}

	if (keyboard.isDown(SDLK_ESCAPE)){
		running = false;
	}

	if (keyboard.isDown(SDLK_LEFT)){
		x -= 5;
	}

	if (keyboard.isDown(SDLK_RIGHT)){
		x += 5;
	}

	if (keyboard.isDown(SDLK_UP)){
		y -= 5;
	}

	if (keyboard.isDown(SDLK_DOWN)){
		y += 5;
	}
}

void Game::handleInput(SDL_Event *event){
	switch (event->type){
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			keyboard.keyPressed(event->key.keysym.sym);
			break;
		case SDL_KEYUP:
			keyboard.keyReleased(event->key.keysym.sym);
			break;
		default:
			break;
	}
}

void Game::draw(){
	//Draw background
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	//Draw stuff
	lole.draw(screenSurface, x, y);
	//Update window surface
	SDL_UpdateWindowSurface(window);
}

void Game::cleanup(){
	SDL_DestroyWindow(window);

	SDL_Quit();
}