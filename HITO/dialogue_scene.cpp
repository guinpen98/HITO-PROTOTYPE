#include <fstream>

#include "dialogue_scene.h"
#include "sentence.h"
#include "analyzer.h"

namespace HITO {
	constexpr int char_size = 256;
	constexpr int text_display_time = 100;

	std::string sjisToUtf8(const std::string sjis) {
		String tmp = Unicode::Widen(sjis);
		return tmp.toUTF8();
	}

	std::string DialogueScene::getKeyword(const Sentence& sentence) const {
		for (int i = 0; i < sentence.size(); ++i) {
			if (!sentence.isThisType("感動詞", i)) continue;
			int index = searchKeyword(sentence.getMorphemes(i));
			if (index == -1) continue;
			return interjection_dictionary[index].value;
		}
		return std::string();
	}

	int DialogueScene::searchKeyword(const std::string& target) const {
		int left = 0, right = (int)interjection_dictionary.size();
		int center = (int)std::floor((left + right) / 2);
		while (left + 1 < right) {
			center = (int)std::floor((left + right) / 2);
			if (target < interjection_dictionary[center].key) right = center;
			else left = center;
		}
		if (interjection_dictionary[left].key == target) return left;
		else return -1;
	}

	DialogueScene::DialogueScene() {
		std::ifstream ifs("interjections.txt");
		std::string str;
		if (ifs.fail()) {
			std::cerr << "Failed to open file." << std::endl;
			return ;
		}
		while (getline(ifs, str)) {
			int index = (int)str.find(" ");
			std::string key = str.substr(0, index);
			std::string value = str.substr(index + 1);
			interjection_dictionary.push_back(KeyValue{ key, value });
		}
	}

	std::string DialogueScene::generateSentence(const std::string& input) {
		std::string parsing_result = Analyzer::morphologicalAnalysis(input);
		Sentence sentence = Analyzer::extractMecabResult(parsing_result);
		std::string keyword = getKeyword(sentence);
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
		mode = Mode::OUTPUT;
	}

	void DialogueScene::setInputMode() {
		mode = Mode::INPUT;
	}

	Mode DialogueScene::getMode() const {
		return mode;
	}
}
