#include <fstream>

#include "dialogue_scene.h"
#include "sentence.h"

namespace HITO {
	constexpr int char_size = 256;
	constexpr int text_display_time = 100;

	std::string DialogueScene::getOutputSentence()const {
		return output_sen;
	}

	std::string DialogueScene::update(const std::string& input) {
		if (dialogue_manager->dialogue_mode == DialogueMode::INIT) {
			return dialogue_manager->initSentence(input);
		}
		if (dialogue_manager->dialogue_mode == DialogueMode::CLOSED_QUESTION) {
			AnswerType answer_type = dialogue_manager->analyzer->closedQuestion(utf8ToSjis(input));
			std::string out_sen;
			switch (answer_type)
			{
			case HITO::AnswerType::YER:
				out_sen = "へ～";
				break;
			case HITO::AnswerType::NO:
				out_sen = "あー、そうなんだ";
				break;
			case HITO::AnswerType::OTHER:
				break;
			default:
				break;
			}
			return sjisToUtf8(out_sen);
		}
		return dialogue_manager->generateSentence(input);
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
		{
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
		}
		return true;
	}
}
