#ifndef HITO_DIALOGUE_H
#define HITO_DIALOGUE_H

#include "data.h"
#include "analyzer.h"

namespace HITO {
	enum class DialogueMode {
		DEFAULT,
		INIT,
		CLOSED_QUESTION
	};

	extern int init_sentence_num;
	extern std::array<std::string, 3> init_sentence;

	std::string sjisToUtf8(const std::string sjis);

	class DialogueManager {
	private:
	public:
		std::unique_ptr<Analyzer> analyzer;
		DialogueMode dialogue_mode = DialogueMode::DEFAULT;
		Data data;

		explicit DialogueManager();
		bool init();
		std::string initSentence(const std::string& input);
		std::string generateSentence(const std::string& input);
	};
}
#endif // !HITO_DIALOGUE_H
