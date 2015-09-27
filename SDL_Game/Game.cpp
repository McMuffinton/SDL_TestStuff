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

Player player(0, 200);
void Game::run(){
	int timeSinceLastFrame;
	int lastFrameStartTime = SDL_GetTicks();
	int frameStartTime;
	int timeSpent;

	while (running){
		frameStartTime = SDL_GetTicks();
		timeSinceLastFrame = frameStartTime - lastFrameStartTime;
		lastFrameStartTime = SDL_GetTicks();

		update(timeSinceLastFrame);

		draw();

		timeSpent = frameStartTime - SDL_GetTicks();

		SDL_Delay((1000 / 60) - timeSpent);
	}
}

void Game::update(int timeSinceLastUpdate){
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0){
		handleInput(&event);
	}

	if (keyboard.isDown(SDLK_ESCAPE)){
		running = false;
	}

	if (keyboard.isDown(SDLK_LEFT) && keyboard.isDown(SDLK_RIGHT)){
		player.stop_x();
	} else if (keyboard.isDown(SDLK_LEFT)){
		player.moveLeft();
	} else if (keyboard.isDown(SDLK_RIGHT)){
		player.moveRight();
	} else {
		player.stop_x();
	}

	if (keyboard.isDown(SDLK_UP) && keyboard.isDown(SDLK_DOWN)){
		player.stop_y();
	}
	else if (keyboard.isDown(SDLK_UP)){
		player.moveUp();
	}
	else if (keyboard.isDown(SDLK_DOWN)){
		player.moveDown();
	}
	else {
		player.stop_y();
	}

	player.update(timeSinceLastUpdate);
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
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	//Draw stuff
	player.draw(screenSurface);
	//Update window surface
	SDL_UpdateWindowSurface(window);
}

void Game::cleanup(){
	SDL_DestroyWindow(window);

	SDL_Quit();
}