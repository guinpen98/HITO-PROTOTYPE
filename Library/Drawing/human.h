#ifndef HITO_HUMAN_H
#define HITO_HUMAN_H
#include "part.h"
#include "configure.h"

namespace HITO {
	class Human
	{
	public:
		Human() : kuchi(window_w / 2, 360), kuchi2(window_w / 2, 360), kuchi3(window_w / 2, 360),
			kao(window_w / 2, 230 + 130), kubi(window_w / 2, 400), dotaimae(window_w / 2, 450), dotaiushiro(window_w / 2, 450),
			me1(window_w / 2, 360), me2(window_w / 2, 360), me3(window_w / 2, 360), me4(window_w / 2, 360), me5(window_w / 2, 360),
			hidarimayu(window_w / 2, 360), migimayu(window_w / 2, 360)
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
}

#endif //!HITO_HUMAN_H
