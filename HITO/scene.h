#ifndef HITO_SCENE_H
#define HITO_SCENE_H

#include "siv_config.h"

namespace HITO {
	class Scene {
	public:
		virtual ~Scene() {}
		virtual GameScene update() = 0;
	};
}

#endif // !HITO_SCENE_H
