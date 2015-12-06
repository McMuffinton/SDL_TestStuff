#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <cmath>
#include <map>
#include "animatedSprite.h"
#include "Sprite.h"

class Keyboard;
class Player {
    // Constants
    const float STOPPED = 0.1f;
    const float ACCEL = 0.001f;
    const float MAXVEL = 0.4f;
    const float INERTIA = 0.85f;

    enum DisplayState { WALKING_LEFT, WALKING_RIGHT, WALKING_UP, WALKING_DOWN, IDLE_LEFT, IDLE_RIGHT };

    std::map<DisplayState, animatedSprite *> sprites;
    void addSprite(DisplayState state, animatedSprite* sprite);

    int x, y;

    DisplayState state;
    DisplayState lastDirection;
    DisplayState direction_x;
    DisplayState direction_y;
    bool walking_x;
    bool walking_y;

    float vel_x, vel_y;
    float accel_x, accel_y;

  public:
    Player(int x, int y);
    ~Player();

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
    void processInput(Keyboard input);
    void update(int timeSinceLastUpdate, Keyboard input);
    void updateStateVariables();

    void limitSpeed(float &velocity, float &acceleration);
};

#endif
