#ifndef HITO_DIALOGUE_H
#define HITO_DIALOGUE_H

#include "data.hpp"
#include "nlu.hpp"

namespace HITO {
	enum class DialogueMode {
		DEFAULT,
		INIT,
		CLOSED_QUESTION
	};

	int init_sentence_num = 0;
	std::array<std::string, 3> init_sentence = { "お名前は何ですか？", "さんであっていますか？", "さんですか、素敵な名前ですね" };

	class DialogueManager {
	private:
		std::unique_ptr<Nlu> nlu;
		std::shared_ptr<Analyzer> analyzer;

		std::string initSentence(const std::string& input) {
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
				AnswerType answer_type = analyzer->closedQuestion(input);
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
			return std::string();
		}


		// std::string closedQuestionSetnence(const std::string& input) {
		// 	AnswerType answer_type = analyzer->closedQuestion(utf8ToSjis(input));
		// 	std::string out_sen;
		// 	switch (answer_type)
		// 	{
		// 	case HITO::AnswerType::YER:
		// 		out_sen = "へ～";
		// 		break;
		// 	case HITO::AnswerType::NO:
		// 		out_sen = "あー、そうなんだ";
		// 		break;
		// 	case HITO::AnswerType::OTHER:
		// 		break;
		// 	default:
		// 		break;
		// 	}
		// 	return sjisToUtf8(out_sen);
		// }

	public:
		DialogueMode dialogue_mode = DialogueMode::DEFAULT;
		Data data;

		explicit DialogueManager() {
			nlu.reset(new Nlu(analyzer));
		}
		bool init() {
			bool is_success = analyzer->init();
			return is_success;
		}

		std::string update(const std::string& input) {
			// 初期設定
			if (dialogue_mode == DialogueMode::INIT) return initSentence(input);

			// if (dialogue_mode == DialogueMode::CLOSED_QUESTION) return closedQuestionSetnence(input); // 

			// 発話理解
			std::string output_sentence = nlu->understandingLanguage(input);
			return output_sentence;

			// 内部状態更新

			// 発話選択

			// 発話生成

		}
	};
}
#endif // !HITO_DIALOGUE_H
