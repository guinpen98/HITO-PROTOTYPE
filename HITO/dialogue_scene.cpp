#include <string>
#include <vector>
#include <fstream>

#include "mecab.h"

#include "stdafx.h"
#include "dialogue_scene.h"
#include "sentence.h"
#include "analyzer.h"

namespace HITO {
	constexpr int char_size = 256;
	constexpr int text_display_time = 5000;

	std::string utf8ToSjis(const std::string utf8) {
		String tmp = Unicode::FromUTF8(utf8);
		return tmp.narrow();
	}

	std::string sjisToUtf8(const std::string sjis) {
		String tmp = Unicode::Widen(sjis);
		return tmp.toUTF8();
	}

	Sentence DialogueScene::extractMecabResult(const std::string& result) {
		std::vector<Morpheme> sentence;
		int cnt = 0;

		std::stringstream ss_result(result);
		std::string line;
		while (std::getline(ss_result, line, '\n')) {
			std::string sjis_line = utf8ToSjis(line);
			int index = (int)sjis_line.find("\t");
			std::string word = sjis_line.substr(0, index);
			std::string category_clump = sjis_line.substr(index + 1);
			if (word == "EOS") break; // 終端の場合

			index = (int)category_clump.find(",");
			std::string type1 = category_clump.substr(0, index);
			category_clump = category_clump.substr(index + 1);
			index = (int)category_clump.find(",");
			std::string type2 = category_clump.substr(0, index);

			sentence.push_back(Morpheme{ word, type1, type2 });
			cnt++;
		}
		return Sentence(sentence, cnt);
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
		MeCab::Tagger* tagger = MeCab::createTagger("");
		const std::string result = tagger->parse(input.c_str());
		Sentence sentence = extractMecabResult(result);
		std::string keyword = getKeyword(sentence);
		if (!keyword.empty()) {
			// ルールベースの会話
			std::string ruled_sen;
			return sjisToUtf8(keyword);
		}
		sentence.preprocess();
		std::string analyzed_result = Analyzer::analyze(sentence);
		if (analyzed_result.empty()) return result;
		return sjisToUtf8(analyzed_result);
	}
	void DialogueScene::update() {
		auto end = std::chrono::system_clock::now();
		auto dur = end - start;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		if (msec > text_display_time) mode = Mode::INPUT;
	}
	void DialogueScene::setOutputMode() {
		mode = Mode::OUTPUT;
		start = std::chrono::system_clock::now();
	}
	Mode DialogueScene::getMode() const {
		return mode;
	}
}
