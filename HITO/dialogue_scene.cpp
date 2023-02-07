#include <fstream>

#include "dialogue_scene.h"
#include "../Library/NLP/sentence.h"

namespace HITO {
	constexpr int char_size = 256;
	constexpr int text_display_time = 100;

	std::string DialogueScene::getOutputSentence()const {
		return output_sen;
	}

	std::string DialogueScene::update(const std::string& input) {
		return dialogue_manager->update(input);
	}

	void DialogueScene::setOutputMode() {
		io_mode = IOMode::OUTPUT;
	}

	void DialogueScene::setInputMode() {
		io_mode = IOMode::INPUT;
	}

	IOMode DialogueScene::getMode() const {
		return io_mode;
	}

	DialogueScene::DialogueScene() : dialogue_manager(new DialogueManager) {

	}

	bool DialogueScene::init() {
		bool is_success = dialogue_manager->init();
		if (!is_success) return false;

		std::ifstream ifs("data.txt");
		std::string str;
		if (ifs.fail()) {
			std::cerr << "Failed to open file." << std::endl;
			dialogue_manager->dialogue_mode = DialogueMode::INIT;
			output_sen = sjisToUtf8(init_sentence[init_sentence_num]);
			init_sentence_num++;
			return true;
		}
		while (getline(ifs, str)) {
			dialogue_manager->data.name = str;
		}
		return true;
	}
}
