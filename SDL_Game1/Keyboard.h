#include <stdio.h>
#include <SDL.h>
#include <map>

class Keyboard{
	//Stores pressed keys
	std::map<SDL_Keycode, bool> keyDown;

public:
	void keyPressed(SDL_Keycode);
	void keyReleased(SDL_Keycode);
	bool isDown(SDL_Keycode);
};