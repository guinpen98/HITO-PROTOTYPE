#include "stdafx.h"
#include "human.h"

void Human::draw()const {
	dotaiushiro.getTexture().drawAt(dotaiushiro.getX(), dotaiushiro.getY());
	kubi.getTexture().drawAt(kubi.getX(), kubi.getY());
	dotaimae.getTexture().drawAt(dotaimae.getX(), dotaimae.getY());
	kao.getTexture().rotatedAt(Vec2{ kao.getTexture().size().x / 2, kao.getTexture().size().y / 2 + 130}, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(kao.getX(), kao.getY());
	Texture kuchi_texture;
	switch (int(Scene::Time() * 6) % 4)
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
	Texture me_texture = me1.getTexture();
	switch (int(Scene::Time() * 70) % 150)
	{
	case 0:
		me_texture = me2.getTexture();
		break;
	case 1:
		me_texture = me3.getTexture();
		break;
	case 2:
		me_texture = me4.getTexture();
		break;
	case 3:
		me_texture = me5.getTexture();
		break;
	case 4:
		me_texture = me4.getTexture();
	case 5:
		me_texture = me3.getTexture();
		break;
	case 6:
		me_texture = me2.getTexture();
		break;
	}
	me_texture.rotatedAt(Vec2{ me_texture.size().x / 2 + 3, me_texture.size().y / 2 + 92 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(me1.getX(), me1.getY());
	hidarimayu.getTexture().rotatedAt(Vec2{ hidarimayu.getTexture().size().x / 2 - 53, hidarimayu.getTexture().size().y / 2 + 129 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(hidarimayu.getX(), hidarimayu.getY());
	migimayu.getTexture().rotatedAt(Vec2{ migimayu.getTexture().size().x / 2 + 60, migimayu.getTexture().size().y / 2 + 129 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(migimayu.getX(), migimayu.getY());
}
