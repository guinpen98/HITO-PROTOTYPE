#ifndef HITO_SWITCHING_SCENE_H
#define HITO_SWITCHING_SCENE_H

#include <chrono>

#include "scene.h"

constexpr int switching_time = 1000; // 1000ミリ秒→1秒

namespace HITO {
	class SwitchingScene : public Scene {
	private:
		std::chrono::system_clock::time_point start;
		GameScene next_scene = GameScene::DIALOGUE;
	public:
		~SwitchingScene() {}
		void restart(GameScene scene);
		GameScene update() override;
		
	};
}

#endif // !HITO_SWITCHING_SCENE_H
