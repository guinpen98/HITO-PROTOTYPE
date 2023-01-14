#include "stdafx.h"
#include "switching_scene.h"

namespace HITO {
	GameScene SwitchingScene::update() {
		auto end = std::chrono::system_clock::now();
		auto dur = end - start;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		if (msec < switching_time) return GameScene::HOME;
		return next_scene;
	}
	void SwitchingScene::restart(GameScene scene) {
		start = std::chrono::system_clock::now();
		next_scene = scene;
	}
}
