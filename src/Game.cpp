#include "Game.h"

Game::Game() {
    if(!init()) {
        printf("Couldn't create the game\n");
    } else {
        run();
    }
}

Game::~Game() {
    cleanup();
}

void Game::addObject(GameObject *toAdd) {
    this->objects.push_back(toAdd);
}

bool Game::init() {
    bool success = true;

    if(SDL_Init(SDL_INIT_EVERYTHING < 0)) {
        printf("Something went wrong while initting: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("Vidya gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) {
            printf("Something went wrong while making a window! : %s\n", SDL_GetError());
            success = false;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

void Game::run() {
    int timeSinceLastFrame;
    int lastFrameStartTime = SDL_GetTicks();
    int frameStartTime;
    int timeSpent;

    this->addObject(new Player(0, 0));
    this->addObject(new Player(10, 10));
    this->addObject(new Player(20, 0));
    this->addObject(new Player(0, 20));
    this->addObject(new Player(20, 20));

    while(running) {
        frameStartTime = SDL_GetTicks();
        timeSinceLastFrame = frameStartTime - lastFrameStartTime;
        lastFrameStartTime = SDL_GetTicks();

        update(timeSinceLastFrame);

        draw();

        timeSpent = frameStartTime - SDL_GetTicks();

        SDL_Delay((1000 / 60) - timeSpent);
    }
}

void Game::handleInput(SDL_Event *event) {
    switch(event->type) {
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

void Game::update(int timeSinceLastUpdate) {
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0) {
        handleInput(&event);
    }

    if(keyboard.isDown(SDLK_ESCAPE)) {
        running = false;
    }

    // Have all GameObjects do their thing with the given input
    for(GameObject* obj : this->objects){
        (*obj).handleInput(this->keyboard);
    }

    // Have all GameObjects update
    for(GameObject* obj : this->objects){
        (*obj).update(timeSinceLastUpdate);
    }
}

void Game::draw() {
    // Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Have all GameObjects draw themselves
    for(GameObject* obj : this->objects){
        (*obj).draw(screenSurface);
    }

    // Update window surface
    SDL_UpdateWindowSurface(window);
}

void Game::cleanup() {
    SDL_DestroyWindow(window);

    SDL_Quit();
}
