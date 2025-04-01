#include "sgg/graphics.h"
#include "util.h"
#include <stdio.h>
#include <string>
#include "gamestate.h"



void init() {
	GameState::getInstance()->init();

	
}

void draw()
{
	GameState::getInstance()->draw();
}

void update(float dt) {
	GameState::getInstance()->update(dt);

}

int main(int argc, char** argv)
{


	graphics::createWindow(800, 800, "Boing Stage1");

	 init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(),
		GameState::getInstance()->getCanvasHeight());

	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();
	return 0;
}