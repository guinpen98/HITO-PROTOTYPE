#include "stdafx.h"
#include "human.h"

void Human::draw()const {
	dotaiushiro.getTexture().drawAt(dotaiushiro.getX(), dotaiushiro.getY());
	kubi.getTexture().drawAt(kubi.getX(), kubi.getY());
	dotaimae.getTexture().drawAt(dotaimae.getX(), dotaimae.getY());
	kao.getTexture().drawAt(kao.getX(), kao.getY());
	kuchi.getTexture().drawAt(kuchi.getX(), kuchi.getY());
}
