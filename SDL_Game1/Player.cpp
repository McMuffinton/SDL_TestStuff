#include "Player.h"

Player::Player(int x, int y){
	//Set up animatedSprites
	int frameDurations[4] = { 15, 15, 15, 15 };
	this->sprites[IDLE_RIGHT] = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 0, 16, 16, 4, frameDurations);
	this->sprites[IDLE_LEFT] = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 16, 16, 16, 4, frameDurations);
	this->sprites[WALKING_LEFT] = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 32, 16, 17, 4, frameDurations);
	this->sprites[WALKING_RIGHT] = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 49, 16, 17, 4, frameDurations);
	this->sprites[WALKING_UP] = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 66, 16, 17, 4, frameDurations);
	this->sprites[WALKING_DOWN] = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 83, 16, 17, 4, frameDurations);

	this->x = x;
	this->y = y;
	this->state = IDLE_RIGHT;
}

Player::~Player(){

}

void Player::moveLeft(){
	accel_x = -ACCEL;
	this->lastDirection = WALKING_LEFT;
}

void Player::moveRight(){
	accel_x = ACCEL;
	this->lastDirection = WALKING_RIGHT;
}

void Player::moveUp(){
	accel_y = -ACCEL;
}

void Player::moveDown(){
	accel_y = ACCEL;
}

void Player::stop_x(){
	accel_x = 0.0f;
}

void Player::stop_y(){
	accel_y = 0.0f;
}

void Player::draw(SDL_Surface* windowSurface){
	this->sprites[state]->draw(windowSurface, this->x, this->y);
}

Player::DisplayState Player::getSprite(){
	if (this->walking_y){
		if (this->direction_y == WALKING_UP){
			return WALKING_UP;
		} else {
			return WALKING_DOWN;
		}
	}
	
	if (this->walking_x){
		if (this->direction_x == WALKING_RIGHT){
			return WALKING_RIGHT;
		}else {
			return WALKING_LEFT;
		}
	}

	if (this->lastDirection == WALKING_LEFT){
		return IDLE_LEFT;
	} else {
		return IDLE_RIGHT;
	}
}

void Player::changeSprite(DisplayState state){
	this->state = state;
}

void Player::updateStateVariables(){
	//Update our walking and direction variables
	if ((vel_y > STOPPED || vel_y < -STOPPED)){
		this->walking_y = true;
		if (this->vel_y > STOPPED){
			this->direction_y = WALKING_DOWN;
		}
		else {
			this->direction_y = WALKING_UP;
		}
	}
	else {
		this->walking_y = false;
	}

	if ((vel_x > STOPPED || vel_x < -STOPPED)){
		this->walking_x = true;
		if (this->vel_x > STOPPED){
			this->direction_x = WALKING_RIGHT;
		}
		else {
			this->direction_x = WALKING_LEFT;
		}
	}
	else {
		this->walking_x = false;
	}
}

void Player::update(int timeSinceLastUpdate){
	updateStateVariables();

	//Change our sprite according to our evaluated state
	changeSprite(getSprite());

	//Update animation frame
	this->sprites[state]->update();

	//Update x and y accel / velocity
	this->x += round(timeSinceLastUpdate * vel_x);
	vel_x += accel_x * timeSinceLastUpdate;

	this->y += round(timeSinceLastUpdate * vel_y);
	vel_y += accel_y * timeSinceLastUpdate;

	//Make sure vel_x don't exceed the max velocity
	if (this->accel_x > 0.0f){
		if (this->vel_x > MAXVEL){
			this->vel_x = MAXVEL;
		}
	} else if (this->accel_x < 0.0f){
		if (this->vel_x < -MAXVEL){
			this->vel_x = -MAXVEL;
		}
	} else {
		this->vel_x = this->vel_x * INERTIA;
	}

	//Make sure vel_y don't exceed the max velocity
	if (this->accel_y > 0.0f){
		if (this->vel_y > MAXVEL){
			this->vel_y = MAXVEL;
		}
	} else if (this->accel_y < 0.0f){
		if (this->vel_y < -MAXVEL){
			this->vel_y = -MAXVEL;
		}
	} else {
		this->vel_y = this->vel_y * INERTIA;
	}
}