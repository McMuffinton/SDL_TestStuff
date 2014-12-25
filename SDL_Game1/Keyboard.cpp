#include "Keyboard.h"

void Keyboard::keyPressed(SDL_Keycode pressed){
	keyDown[pressed] = true;
}

void Keyboard::keyReleased(SDL_Keycode released){
	keyDown[released] = false;
}

bool Keyboard::isDown(SDL_Keycode query){
	return keyDown[query];
}
