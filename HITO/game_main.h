#ifndef HITO_GAME_MAIN_H
#define HITO_GAME_MAIN_H

#include <memory>
#include <array>

#include "home_scene.h"
#include "dialogue_scene.h"
#include "drawing.h"

namespace HITO {
	class GameMain {
		std::unique_ptr<Drawing> drawing;
		GameScene current_scene = GameScene::HOME;
	public:
		std::array<std::unique_ptr<Scene>, scene_num> scene_list;
		explicit GameMain() : drawing(new Drawing) {
			drawing->init();
			scene_list[0] = std::make_unique<HomeScene>();
			scene_list[1] = std::make_unique<DialogueScene>();
		}
		void update();
	};
}

#endif // !HITO_GAME_MAIN_H
