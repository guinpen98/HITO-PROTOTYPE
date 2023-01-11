#ifndef HITO_GAME_MAIN_H
#define HITO_GAME_MAIN_H

#include <memory>
#include <vector>

#include "scene.h"
#include "home_scene.h"

namespace HITO {
	class GameMain {
	public:
		std::vector<std::unique_ptr<Scene>> main_list;
		explicit GameMain() {
			main_list.resize(1);
			main_list[0] = std::make_unique<HomeScene>();
		}
	};
}

#endif // !HITO_GAME_MAIN_H
