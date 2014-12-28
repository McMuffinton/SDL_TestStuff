#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <cmath>
#include "animatedSprite.h"
#include "Sprite.h"

class Player{

	const float ACCEL = 0.001f;
	const float MAXVEL = 0.3f;
	const float INERTIA = 0.85f;

	animatedSprite* sprite;

	int x, y;
	float vel_x, vel_y;
	float accel_x, accel_y;

	public:
		Player(int x, int y);
		~Player();

		void moveLeft();
		void moveRight();

		void moveUp();
		void moveDown();

		void stop_x();
		void stop_y();

		void draw(SDL_Surface* windowSurface);
		void update(int timeSinceLastUpdate);
};

#endif