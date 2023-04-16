#ifndef HITO_DIALOGUE_H
#define HITO_DIALOGUE_H

#include "data.h"
#include "nlu.h"

namespace HITO {
	enum class DialogueMode {
		DEFAULT,
		INIT,
		CLOSED_QUESTION
	};

	extern int init_sentence_num;
	extern std::array<std::string, 3> init_sentence;

	class DialogueManager {
	private:
		std::unique_ptr<Nlu> nlu;
		std::shared_ptr<Analyzer> analyzer;

		std::string initSentence(const std::string& input);
		//std::string closedQuestionSetnence(const std::string& input);
	public:
		DialogueMode dialogue_mode = DialogueMode::DEFAULT;
		Data data;

		explicit DialogueManager();
		bool init();
		std::string update(const std::string& input);
	};
}
#endif // !HITO_DIALOGUE_H