#ifndef HITO_SIV_CONFIG_H
#define HITO_SIV_CONFIG_H
#include <Siv3D.hpp> // OpenSiv3D v0.6.5

#include "configure.h"

constexpr Rect area{ window_w / 2 - 250, window_h - 200, 500, 160 };

struct SivConfig {
	const Font font{ 40 };
	const Font text_font{ 30 };
};

#endif // !HITO_SIV_CONFIG_H

