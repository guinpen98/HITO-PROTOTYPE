#ifndef HITO_HOME_SCENE_H
#define HITO_HOME_SCENE_H

#include "scene.h"

namespace HITO {
	class HomeScene : public Scene {
	public:
		~HomeScene() {}
		GameScene update() override;
	};
}

#endif // !HITO_HOME_SCENE_H
