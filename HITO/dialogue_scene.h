#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include "scene.h"

namespace HITO {
	struct KeyValue {
		const std::string key;
		const std::string value;
	};

	class DialogueScene : public Scene {
	private:
		std::vector<KeyValue> interjection_dictionary;

		class Sentence extractMecabResult(const std::string& result);
		std::string getKeyword(const Sentence& sentence)const;
		int searchKeyword(const std::string& target)const;
	public:
		DialogueScene();
		~DialogueScene() {}
		GameScene update() override;
		std::string update(const std::string& input);
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
