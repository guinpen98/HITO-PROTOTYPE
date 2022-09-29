#include "stdafx.h"
#include "human.h"

void Human::draw()const {
	dotaiushiro.getTexture().drawAt(dotaiushiro.getX(), dotaiushiro.getY());
	kubi.getTexture().drawAt(kubi.getX(), kubi.getY());
	dotaimae.getTexture().drawAt(dotaimae.getX(), dotaimae.getY());
	kao.getTexture().rotatedAt(Vec2{ kao.getTexture().size().x / 2, kao.getTexture().size().y / 2 + 130}, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(kao.getX(), kao.getY());
	Texture kuchi_texture;
	switch ((int)Scene::Time() % 4)
	{
	case 0:
		kuchi_texture = kuchi.getTexture();
		break;
	case 1:
		kuchi_texture = kuchi3.getTexture();
		break;
	case 2:
		kuchi_texture = kuchi2.getTexture();
		break;
	case 3:
		kuchi_texture = kuchi3.getTexture();
		break;
	}
	kuchi_texture.rotatedAt(Vec2{ kuchi_texture.size().x / 2, kuchi_texture.size().y / 2}, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(kuchi.getX(), kuchi.getY());
}
