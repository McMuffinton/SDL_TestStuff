#include "Player.h"
#include "Keyboard.h"

Player::Player(int x, int y) {
    // Set up animatedSprites
    int frameDurations[4] = {15, 15, 15, 15};

    // clang-format off
    this->addSprite(DisplayState::IDLE_RIGHT,    new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 0, 16, 16, 4, frameDurations));
    this->addSprite(DisplayState::IDLE_LEFT,     new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 16, 16, 16, 4, frameDurations));
    this->addSprite(DisplayState::WALKING_LEFT,  new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 32, 16, 17, 4, frameDurations));
    this->addSprite(DisplayState::WALKING_RIGHT, new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 49, 16, 17, 4, frameDurations));
    this->addSprite(DisplayState::WALKING_UP,    new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 66, 16, 17, 4, frameDurations));
    this->addSprite(DisplayState::WALKING_DOWN,  new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 83, 16, 17, 4, frameDurations));
    // clang-format on

    this->x = x;
    this->y = y;

    this->lastDirection = DisplayState::WALKING_RIGHT;
    this->state = DisplayState::IDLE_RIGHT;
}

Player::~Player() {
    // Clean up animatedSprites
    for(auto &sprite : this->sprites) {
        delete sprite.second;
    }
}

void Player::addSprite(DisplayState state, animatedSprite *sprite) {
    this->sprites[state] = sprite;
}

void Player::moveLeft() {
    this->accel_x = -ACCEL;
    this->lastDirection = DisplayState::WALKING_LEFT;
}

void Player::moveRight() {
    this->accel_x = ACCEL;
    this->lastDirection = DisplayState::WALKING_RIGHT;
}

void Player::moveUp() {
    this->accel_y = -ACCEL;
}

void Player::moveDown() {
    this->accel_y = ACCEL;
}

void Player::stop_x() {
    this->accel_x = 0.0f;
}

void Player::stop_y() {
    this->accel_y = 0.0f;
}

void Player::draw(SDL_Surface *windowSurface) {
    this->sprites[state]->draw(windowSurface, this->x, this->y);
}

Player::DisplayState Player::getSprite() {
    if(this->walking_y) {
        if(this->direction_y == DisplayState::WALKING_UP) {
            return DisplayState::WALKING_UP;
        } else {
            return DisplayState::WALKING_DOWN;
        }
    }

    if(this->walking_x) {
        if(this->direction_x == DisplayState::WALKING_RIGHT) {
            return DisplayState::WALKING_RIGHT;
        } else {
            return DisplayState::WALKING_LEFT;
        }
    }

    if(this->lastDirection == DisplayState::WALKING_LEFT) {
        return DisplayState::IDLE_LEFT;
    } else {
        return DisplayState::IDLE_RIGHT;
    }
}

void Player::changeSprite(DisplayState state) {
    this->state = state;
}

void Player::updateStateVariables() {
    // Update our walking and direction variables
    if((this->vel_y > STOPPED || this->vel_y < -STOPPED)) {
        this->walking_y = true;
        if(this->vel_y > STOPPED) {
            this->direction_y = DisplayState::WALKING_DOWN;
        } else {
            this->direction_y = DisplayState::WALKING_UP;
        }
    } else {
        this->walking_y = false;
    }

    if((this->vel_x > STOPPED || this->vel_x < -STOPPED)) {
        this->walking_x = true;
        if(this->vel_x > STOPPED) {
            this->direction_x = DisplayState::WALKING_RIGHT;
        } else {
            this->direction_x = DisplayState::WALKING_LEFT;
        }
    } else {
        this->walking_x = false;
    }
}

void Player::limitSpeed(float &velocity, float &acceleration) {
    if(acceleration > 0.0f) {
        if(velocity > MAXVEL) {
            velocity = MAXVEL;
        }
    } else if(acceleration < 0.0f) {
        if(velocity < -MAXVEL) {
            velocity = -MAXVEL;
        }
    } else {
        velocity = velocity * INERTIA;
    }
}

void Player::handleInput(Keyboard input) {
    if(input.isDown(SDLK_LEFT) && input.isDown(SDLK_RIGHT)) {
        this->stop_x();
    } else if(input.isDown(SDLK_LEFT)) {
        this->moveLeft();
    } else if(input.isDown(SDLK_RIGHT)) {
        this->moveRight();
    } else {
        this->stop_x();
    }

    if(input.isDown(SDLK_UP) && input.isDown(SDLK_DOWN)) {
        this->stop_y();
    } else if(input.isDown(SDLK_UP)) {
        this->moveUp();
    } else if(input.isDown(SDLK_DOWN)) {
        this->moveDown();
    } else {
        this->stop_y();
    }
}

void Player::update(int timeSinceLastUpdate) {
    updateStateVariables();

    // Change our sprite according to our evaluated state
    changeSprite(getSprite());

    // Update animation frame
    this->sprites[state]->update();

    // Update x and y accel / velocity
    this->x += round(timeSinceLastUpdate * this->vel_x);
    this->vel_x += this->accel_x * timeSinceLastUpdate;

    this->y += round(timeSinceLastUpdate * this->vel_y);
    this->vel_y += this->accel_y * timeSinceLastUpdate;

    // Make sure vel_x don't exceed the max velocity
    limitSpeed(this->vel_x, this->accel_x);

    // Make sure vel_y don't exceed the max velocity
    limitSpeed(this->vel_y, this->accel_y);
}
