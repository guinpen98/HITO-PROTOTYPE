#ifndef HITO_HUMAN_H
#define HITO_HUMAN_H
#include "part.h"
class Human
{
	Part kuchi;
	Part kuchi2;
	Part kuchi3;
	Part me1;
	Part me2;
	Part me3;
	Part me4;
	Part me5;
	Part hidarimayu;
	Part migimayu;
	Part kao;
	Part kubi;
	Part dotaimae;
	Part dotaiushiro;
public:
	Human() : kuchi(U"img/human/kuchi.png", 256, 360), kuchi2(U"img/human/kuchi2.png", 256, 360), kuchi3(U"img/human/kuchi3.png", 256, 360),
		kao(U"img/human/kao.png", 256, 230 + 130), kubi(U"img/human/kubi.png", 256, 400), dotaimae(U"img/human/dotaimae.png", 256, 450), dotaiushiro(U"img/human/dotaiushiro.png", 256, 450),
		me1(U"img/human/me1.png", 256, 360), me2(U"img/human/me2.png", 256, 360), me3(U"img/human/me3.png", 256, 360), me4(U"img/human/me4.png", 256, 360), me5(U"img/human/me5.png", 256, 360),
		hidarimayu(U"img/human/hidarimayu.png", 256, 360), migimayu(U"img/human/migimayu.png", 256, 360)
	{

	};
	void draw()const;
};
#endif //!HITO_HUMAN_H
