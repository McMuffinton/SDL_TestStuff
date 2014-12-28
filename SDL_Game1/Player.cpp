#include "Player.h"

Player::Player(int x, int y){
	int frameDurations[4] = { 15, 15, 15, 15 };
	this->sprite = new animatedSprite("res/img/AW_Soldier.bmp", 200, 200, 200, 0, 0, 16, 16, 4, frameDurations);

	this->x = x;
	this->y = y;
}

Player::~Player(){

}

void Player::moveLeft(){
	accel_x = -ACCEL;
}

void Player::moveRight(){
	accel_x = ACCEL;
}

void Player::stop(){
	accel_x = 0.0f;
}

void Player::draw(SDL_Surface* windowSurface){
	this->sprite->draw(windowSurface, this->x, this->y);
}

void Player::update(int timeSinceLastUpdate){
	this->sprite->update();

	this->x += round(timeSinceLastUpdate * vel_x);
	vel_x += accel_x * timeSinceLastUpdate;

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
}