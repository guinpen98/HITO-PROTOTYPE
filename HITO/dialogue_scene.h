#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include "scene.h"
#include "word.h"

namespace HITO {
	class DialogueScene : public Scene {
	private:
		Word extractMecabResult(const std::string& result);
		void combineMorphemes(Word& word);

	public:
		~DialogueScene() {}
		GameScene update() override;
		std::string update(const std::string& input);
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
