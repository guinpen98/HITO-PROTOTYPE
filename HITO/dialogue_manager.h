#ifndef HITO_DIALOGUE_H
#define HITO_DIALOGUE_H

#include "analyzer.h"

namespace HITO {
	std::string sjisToUtf8(const std::string sjis);

	class DialogueManager {
	private:
	public:
		std::unique_ptr<Analyzer> analyzer;

		explicit DialogueManager();
		bool init();
		std::string generateSentence(const std::string& input);
	};
}
#endif // !HITO_DIALOGUE_H
