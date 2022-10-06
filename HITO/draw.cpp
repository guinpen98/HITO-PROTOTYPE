#include "stdafx.h"
#include "draw.h"

void Draw::characterDraw(Human human) const
{
	human.dotaiushiro.getTexture().drawAt(human.dotaiushiro.getX(), human.dotaiushiro.getY());
	human.kubi.getTexture().drawAt(human.kubi.getX(), human.kubi.getY());
	human.dotaimae.getTexture().drawAt(human.dotaimae.getX(), human.dotaimae.getY());
	human.kao.getTexture().rotatedAt(Vec2{ human.kao.getTexture().size().x / 2, human.kao.getTexture().size().y / 2 + 130 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human.kao.getX(), human.kao.getY());
	Texture kuchi_texture;
	switch (int(Scene::Time() * 6) % 4)
	{
	case 0:
		kuchi_texture = human.kuchi.getTexture();
		break;
	case 1:
		kuchi_texture = human.kuchi3.getTexture();
		break;
	case 2:
		kuchi_texture = human.kuchi2.getTexture();
		break;
	case 3:
		kuchi_texture = human.kuchi3.getTexture();
		break;
	}
	kuchi_texture.rotatedAt(Vec2{ kuchi_texture.size().x / 2, kuchi_texture.size().y / 2 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human.kuchi.getX(), human.kuchi.getY());
	Texture me_texture = human.me1.getTexture();
	switch (int(Scene::Time() * 70) % 150)
	{
	case 0:
		me_texture = human.me2.getTexture();
		break;
	case 1:
		me_texture = human.me3.getTexture();
		break;
	case 2:
		me_texture = human.me4.getTexture();
		break;
	case 3:
		me_texture = human.me5.getTexture();
		break;
	case 4:
		me_texture = human.me4.getTexture();
	case 5:
		me_texture = human.me3.getTexture();
		break;
	case 6:
		me_texture = human.me2.getTexture();
		break;
	}
	me_texture.rotatedAt(Vec2{ me_texture.size().x / 2 + 3, me_texture.size().y / 2 + 92 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human.me1.getX(), human.me1.getY());
	human.hidarimayu.getTexture().rotatedAt(Vec2{ human.hidarimayu.getTexture().size().x / 2 - 53, human.hidarimayu.getTexture().size().y / 2 + 129 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human.hidarimayu.getX(), human.hidarimayu.getY());
	human.migimayu.getTexture().rotatedAt(Vec2{ human.migimayu.getTexture().size().x / 2 + 60, human.migimayu.getTexture().size().y / 2 + 129 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human.migimayu.getX(), human.migimayu.getY());
}
