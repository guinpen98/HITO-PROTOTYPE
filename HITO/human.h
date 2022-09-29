#ifndef HITO_HUMAN_H
#define HITO_HUMAN_H
#include "part.h"
class Human
{
	Part kuchi;
	Part kao;
	Part kubi;
	Part dotaimae;
	Part dotaiushiro;
public:
	Human() : kuchi(U"img/human/kuchi.png", 256, 330), kao(U"img/human/kao.png", 256, 200),
		kubi(U"img/human/kubi.png", 256, 400), dotaimae(U"img/human/dotaimae.png", 256, 450), dotaiushiro(U"img/human/dotaiushiro.png", 256, 450)
	{

	};
	void draw()const;
};
#endif //!HITO_HUMAN_H
