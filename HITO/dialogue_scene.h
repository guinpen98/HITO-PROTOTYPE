#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

namespace HITO {
	struct KeyValue {
		const std::string key;
		const std::string value;
	};

	enum class IOMode {
		INPUT
		, OUTPUT
	};

	enum class DialogueMode {
		DEFAULT,
		CLOSED_QUESTION
	};

	class DialogueScene{
	private:
		std::vector<KeyValue> interjection_dictionary;
		std::vector<std::string> affirmation_dictionary;
		std::vector<std::string> denial_dictionary;
		IOMode io_mode = IOMode::INPUT;
		DialogueMode dialogue_mode = DialogueMode::DEFAULT;

		std::string getKeyword(const class Sentence& sentence, bool is_ruled_base)const;
		int searchKeyword(const std::string& target)const;
		std::string closedQuestion(const std::string& input);
		bool searchWord(const std::string& target, const std::vector<std::string> dictionary)const;
	public:
		explicit DialogueScene();
		std::string generateSentence(const std::string& input);
		void setOutputMode();
		void setInputMode();
		IOMode getMode()const;
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
