#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <cmath>
#include <map>
#include "animatedSprite.h"
#include "Sprite.h"
#include "GameObject.h"

class Keyboard;
class Player : public GameObject {
    // Constants
    const float STOPPED = 0.1f;
    const float ACCEL = 0.001f;
    const float MAXVEL = 0.4f;
    const float INERTIA = 0.85f;

    enum DisplayState { WALKING_LEFT, WALKING_RIGHT, WALKING_UP, WALKING_DOWN, IDLE_LEFT, IDLE_RIGHT };

    std::map<DisplayState, animatedSprite *> sprites;
    void addSprite(DisplayState state, animatedSprite *sprite);

    DisplayState state;
    DisplayState lastDirection;
    DisplayState direction_x;
    DisplayState direction_y;
    bool walking_x = false;
    bool walking_y = false;

    float vel_x = 0, vel_y = 0;
    float accel_x = 0, accel_y = 0;

  public:
    Player(int x, int y);
    ~Player();

    int x, y;

    // Movement functions
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stop_x();
    void stop_y();

    DisplayState getSprite();
    void changeSprite(DisplayState state);

    void draw(SDL_Surface *windowSurface);
    void handleInput(Keyboard input);
    void update(int timeSinceLastUpdate);
    void updateStateVariables();

    void limitSpeed(float &velocity, float &acceleration);
};

#endif
