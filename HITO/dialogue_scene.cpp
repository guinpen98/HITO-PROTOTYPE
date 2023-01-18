#include <string>
#include <vector>

#include "mecab.h"

#include "stdafx.h"
#include "dialogue_scene.h"
#include "sentence.h"
#include "analyzer.h"

namespace HITO {
	constexpr int char_size = 256;

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

	GameScene DialogueScene::update() {
		return GameScene::DIALOGUE;
    }

	std::string DialogueScene::update(const std::string& input) {
		if (input == "") return input;
		
		MeCab::Tagger* tagger = MeCab::createTagger("");
		const std::string result = tagger->parse(input.c_str());
		Sentence sentence = extractMecabResult(result);
		bool isKeyword = sentence.preprocess();
		if (isKeyword) {
			// ルールベースの会話
			std::string ruled_sen;
			return ruled_sen;
		}
		Analyzer::analyze(sentence);

		return result;
	}
}
