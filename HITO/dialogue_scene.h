﻿#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include "scene.h"

namespace HITO {
	struct KeyValue {
		const std::string key;
		const std::string value;
	};

	enum class Mode {
		INPUT
		, OUTPUT
	};

	class DialogueScene{
	private:
		std::vector<KeyValue> interjection_dictionary;
		std::chrono::system_clock::time_point start;
		Mode mode = Mode::INPUT;

		class Sentence extractMecabResult(const std::string& result);
		std::string getKeyword(const Sentence& sentence)const;
		int searchKeyword(const std::string& target)const;
	public:
		DialogueScene();
		std::string generateSentence(const std::string& input);
		void update();
		void setOutputMode();
		Mode getMode()const;
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
