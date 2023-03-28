#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include <NLP/dialogue_manager.h>

namespace HITO {
	enum class IOMode {
		INPUT
		, OUTPUT
	};

	class DialogueScene{
	private:
		std::string output_sen;
		IOMode io_mode = IOMode::INPUT;
	public:
		std::unique_ptr<DialogueManager> dialogue_manager;

		explicit DialogueScene();
		bool init();
		std::string update(const std::string& input);
		void setOutputMode();
		void setInputMode();
		std::string getOutputSentence()const;
		IOMode getMode()const;
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
