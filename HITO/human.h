#ifndef HITO_HUMAN_H
#define HITO_HUMAN_H
#include "part.h"
class Human
{
public:
	Human() : kuchi(256, 360), kuchi2(256, 360), kuchi3(256, 360),
		kao(256, 230 + 130), kubi(256, 400), dotaimae(256, 450), dotaiushiro(256, 450),
		me1(256, 360), me2(256, 360), me3(256, 360), me4(256, 360), me5(256, 360),
		hidarimayu(256, 360), migimayu(256, 360)
	{};
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
};
#endif //!HITO_HUMAN_H
