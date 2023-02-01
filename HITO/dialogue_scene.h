#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H
#include "data.h"

#include "analyzer.h"
#include "dialogue_manager.h"

namespace HITO {
	enum class IOMode {
		INPUT
		, OUTPUT
	};

	enum class DialogueMode {
		DEFAULT,
		INIT,
		CLOSED_QUESTION
	};

	class DialogueScene{
	private:
		std::unique_ptr<DialogueManager> dialogue_manager;
		std::string output_sen;
		IOMode io_mode = IOMode::INPUT;
		DialogueMode dialogue_mode = DialogueMode::DEFAULT;
	public:
		explicit DialogueScene();
		bool init();
		std::string update(const std::string& input);
		void setOutputMode();
		void setInputMode();
		std::string getOutputSentence()const;
		IOMode getMode()const;
		Data data;
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
