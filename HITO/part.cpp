#include "stdafx.h"
#include "part.h"


int Part::getX() const
{
	return x;
}

int Part::getY() const
{
	return y;
}
Texture Part::getTexture()const {
	return texture;
}

void Part::setAngle(const float new_angle)
{
	angle = new_angle;
}

float Part::getAngle() const
{
	return angle;
}
