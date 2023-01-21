#ifndef HITO_GAME_MAIN_H
#define HITO_GAME_MAIN_H
#include "home_scene.h"
#include "dialogue_scene.h"
#include "drawing.h"

namespace HITO {
	class GameMain {
		std::unique_ptr<Drawing> drawing;
		GameScene current_scene = GameScene::HOME;
		std::unique_ptr<HomeScene> home_scene;
		std::unique_ptr<class DialogueScene> dialogue_scene;
	public:
		explicit GameMain();
		void update();
		void homeScene();
		void dialogueScene();
	};
}

#endif // !HITO_GAME_MAIN_H
