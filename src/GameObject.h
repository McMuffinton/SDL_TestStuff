#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL2/SDL.h>

class Keyboard;
class GameObject {
  public:
    GameObject(){};
    virtual ~GameObject(){};

    // clang-format off
    virtual void handleInput(Keyboard input)     =0;
    virtual void update(int timeSinceLastUpdate) =0;
    virtual void draw(SDL_Surface* windowSurface)=0;
    // clang-format on
};

#endif  // GAMEOBJECT_H
