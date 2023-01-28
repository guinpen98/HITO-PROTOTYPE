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

	std::string DialogueScene::getKeyword(const Sentence& sentence, bool is_ruled_base = false) const {
		for (int i = 0; i < sentence.size(); ++i) {
			if (!sentence.isThisType("感動詞", i)) continue;
			int index = searchKeyword(sentence.getMorphemes(i));
			if (index == -1) continue;
			if(is_ruled_base) return interjection_dictionary[index].value;
			return interjection_dictionary[index].key;
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

	std::string DialogueScene::closedQuestion(const std::string& input) {
		std::string word = input;
		word.erase(word.size() - 1);
		bool is_affirmation = searchWord(word, affirmation_dictionary);
		if (is_affirmation) {
			return "へ～";
		}
		bool is_denial = searchWord(word, denial_dictionary);
		if (is_denial) {
			return "あー、そうなんだ";
		}
		return std::string();
	}

	bool DialogueScene::searchWord(const std::string& target, const std::vector<std::string> dictionary) const {
		int left = 0, right = (int)dictionary.size();
		int center = (int)std::floor((left + right) / 2);
		while (left + 1 < right) {
			center = (int)std::floor((left + right) / 2);
			if (target < dictionary[center]) right = center;
			else left = center;
		}
		return dictionary[left] == target;
	}

	int init_sentence_num = 0;
	std::array<std::string, 2> init_sentence = { "お名前は何ですか？", "さんですか、素敵な名前ですね" };

	std::string DialogueScene::generateSentence(const std::string& input) {
		if (dialogue_mode == DialogueMode::INIT) {
			if (init_sentence_num == 0) {
				std::string output_sen = sjisToUtf8(init_sentence[init_sentence_num]);
				init_sentence_num++;
				return output_sen;
			}
			std::string name = input;
			name.erase(name.size() - 1);
			data.name = name;
			dialogue_mode = DialogueMode::DEFAULT;
			return data.name + sjisToUtf8(init_sentence[init_sentence_num]);
		}
		if (dialogue_mode == DialogueMode::CLOSED_QUESTION) {
			return sjisToUtf8(closedQuestion(utf8ToSjis(input)));
		}
		std::string parsing_result = Analyzer::morphologicalAnalysis(input);
		Sentence sentence = Analyzer::extractMecabResult(parsing_result);
		std::string keyword = getKeyword(sentence, true);
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
	bool DialogueScene::init() {
		{
			std::ifstream ifs("interjections.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				return false;
			}
			while (getline(ifs, str)) {
				int index = (int)str.find(" ");
				std::string key = str.substr(0, index);
				std::string value = str.substr(index + 1);
				interjection_dictionary.push_back(KeyValue{ key, value });
			}
		}
		{
			std::ifstream ifs("affirmation.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				return false;
			}
			while (getline(ifs, str)) {
				affirmation_dictionary.push_back(str);
			}
		}
		{
			std::ifstream ifs("denial.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				return false;
			}
			while (getline(ifs, str)) {
				denial_dictionary.push_back(str);
			}
		}
		{
			std::ifstream ifs("data.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				dialogue_mode = DialogueMode::INIT;
				return true;
			}
			while (getline(ifs, str)) {
				data.name = str;
			}
		}
		return true;
	}
}
