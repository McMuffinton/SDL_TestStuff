#include <stdio.h>
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "Keyboard.h"
#include "animatedSprite.h"
#include "Player.h"
#include "GameObject.h"

class Game {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    Keyboard keyboard;

    bool running = true;

  public:
    Game();
    ~Game();

    vector<GameObject*> objects;
    void addObject(GameObject* toAdd);

    bool init();
    void run();
    void handleInput(SDL_Event* event);
    void update(int timeSinceLastUpdate);
    void draw();
    void cleanup();
};
