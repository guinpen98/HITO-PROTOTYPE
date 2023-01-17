#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include "scene.h"

using CategoryList = std::vector<std::string>;
using CategoryListPair = std::pair<CategoryList, CategoryList>;
using WordList = std::vector<std::string>;

namespace HITO {
	class DialogueScene : public Scene {
	private:
		std::pair<WordList, CategoryListPair> convertMecabResult(const std::string& result);

	public:
		~DialogueScene() {}
		GameScene update() override;
		std::string update(const std::string& input);
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
