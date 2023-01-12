#ifndef HITO_GAME_MAIN_H
#define HITO_GAME_MAIN_H

#include <memory>
#include <array>

#include "scene.h"
#include "home_scene.h"

namespace HITO {
	class GameMain {
	public:
		std::array<std::unique_ptr<Scene>, 1> scene_list;
		explicit GameMain() {
			scene_list[0] = std::make_unique<HomeScene>();
		}
	};
}

#endif // !HITO_GAME_MAIN_H
