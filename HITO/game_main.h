#ifndef HITO_GAME_MAIN_H
#define HITO_GAME_MAIN_H

#include <memory>
#include <vector>

#include "main.h"
#include "home_main.h"

namespace Game {
	class GameMain {
	public:
		std::vector<std::unique_ptr<Main>> main_list;
		explicit GameMain() {
			main_list.resize(1);
			main_list[0] = std::make_unique<HomeMain>();
		}
	};
}

#endif // !HITO_GAME_MAIN_H
