#include <stdio.h>
#include <vector>
#include "sprite.h"

class animatedSprite : public Sprite{
	int totalSprites;
	vector<int> framesPerSprite;

	int currentSprite = 0;
	int framesSinceLastUpdate = 0;

	int stepWidth;


public:
	animatedSprite(string imagePath,
		uint8_t R, uint8_t G, uint8_t B,
		int src_x, int src_y,
		int src_width, int src_height,
		int totalSprites, int framesPerSprite[]);

	animatedSprite(string imagePath,
		int src_x, int src_y,
		int src_width, int src_height,
		int totalSprites, int framesPerSprite[]);

	void update();

	~animatedSprite();
};