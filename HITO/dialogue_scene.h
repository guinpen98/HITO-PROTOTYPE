#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include "scene.h"

namespace HITO {
	class DialogueScene : public Scene {
	private:
		class Sentence extractMecabResult(const std::string& result);

	public:
		~DialogueScene() {}
		GameScene update() override;
		std::string update(const std::string& input);
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
