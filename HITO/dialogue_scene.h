#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include "scene.h"

namespace HITO {
	class DialogueScene : public Scene {
	public:
		~DialogueScene() {}
		GameScene update() override;
		std::string update(std::string& input);
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
