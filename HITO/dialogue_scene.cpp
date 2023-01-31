#include <fstream>

#include "dialogue_scene.h"
#include "sentence.h"

namespace HITO {
	constexpr int char_size = 256;
	constexpr int text_display_time = 100;

	std::string sjisToUtf8(const std::string sjis) {
		String tmp = Unicode::Widen(sjis);
		return tmp.toUTF8();
	}

	std::string DialogueScene::getOutputSentence()const {
		return output_sen;
	}

	int init_sentence_num = 0;
	std::array<std::string, 3> init_sentence = { "お名前は何ですか？", "さんであっていますか？", "さんですか、素敵な名前ですね"};

	std::string DialogueScene::generateSentence(const std::string& input) {
		if (dialogue_mode == DialogueMode::INIT) {
			if (init_sentence_num == 0) {
				std::string out_sen = sjisToUtf8(init_sentence[init_sentence_num]);
				init_sentence_num++;
				return out_sen;
			}

			if (init_sentence_num == 1) {
				std::string name = input;
				name.erase(name.size() - 1);
				data.name = name;
				std::string out_sen = data.name + sjisToUtf8(init_sentence[init_sentence_num]);
				init_sentence_num++;
				return out_sen;
			}

			if (init_sentence_num == 2) {
				AnswerType answer_type = analyzer->closedQuestion(utf8ToSjis(input));
				std::string out_sen;
				switch (answer_type)
				{
				case HITO::AnswerType::YER:
					dialogue_mode = DialogueMode::DEFAULT;
					out_sen = data.name + sjisToUtf8(init_sentence[init_sentence_num]);
					break;
				case HITO::AnswerType::NO:
					init_sentence_num = 0;
					out_sen = sjisToUtf8(init_sentence[init_sentence_num]);
					init_sentence_num++;
					break;
				case HITO::AnswerType::OTHER:
					init_sentence_num = 0;
					out_sen = sjisToUtf8(init_sentence[init_sentence_num]);
					init_sentence_num++;
					break;
				default:
					break;
				}
				return out_sen;
			}
		}
		if (dialogue_mode == DialogueMode::CLOSED_QUESTION) {
			AnswerType answer_type = analyzer->closedQuestion(utf8ToSjis(input));
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
		std::string parsing_result = Analyzer::morphologicalAnalysis(input);
		Sentence sentence = Analyzer::extractMecabResult(parsing_result);
		std::string keyword = analyzer->getKeyword(sentence, true);
		if (!keyword.empty()) {
			// ルールベースの会話
			std::string rule_based_sen;
			return sjisToUtf8(keyword);
		}
		sentence.preprocess();
		std::string analysis_result = Analyzer::analyze(sentence);
		if (analysis_result.empty()) return parsing_result;
		Analyzer::semanticAnalysis(analysis_result);
		return sjisToUtf8(analysis_result);
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
	DialogueScene::DialogueScene() : analyzer(new Analyzer) {

	}
	bool DialogueScene::init() {
		{
			bool is_success = analyzer->init();
			if (!is_success) return false;

			std::ifstream ifs("data.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				dialogue_mode = DialogueMode::INIT;
				output_sen = sjisToUtf8(init_sentence[init_sentence_num]);
				init_sentence_num++;
				return true;
			}
			while (getline(ifs, str)) {
				data.name = str;
			}
		}
		return true;
	}
}
