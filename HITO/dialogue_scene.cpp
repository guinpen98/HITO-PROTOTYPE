#include <string>
#include <vector>

#include "mecab.h"

#include "stdafx.h"
#include "dialogue_scene.h"

namespace HITO {
	constexpr int char_size = 256;

	std::string utf8ToSjis(const std::string utf8) {
		String tmp = Unicode::FromUTF8(utf8);
		return tmp.narrow();
	}

	std::pair<WordList, CategoryListPair> DialogueScene::convertMecabResult(const std::string& result) {
		WordList word_list;
		CategoryList category_list1;
		CategoryList category_list2;
		std::stringstream ss_result(result);
		std::string line;
		while (std::getline(ss_result, line, '\n')) {
			std::string sjis_line = utf8ToSjis(line);
			int index = (int)sjis_line.find("\t");
			std::string word = sjis_line.substr(0, index);
			std::string category_clump = sjis_line.substr(index + 1);
			word_list.push_back(word);

			index = (int)category_clump.find(",");
			std::string category1 = category_clump.substr(0, index);
			category_clump = category_clump.substr(index + 1);
			index = (int)category_clump.find(",");
			std::string category2 = category_clump.substr(0, index);

			category_list1.push_back(category1);
			category_list2.push_back(category2);
		}
		return { word_list, {category_list1, category_list2} };
	}

	GameScene DialogueScene::update() {
		return GameScene::DIALOGUE;
    }

	std::string DialogueScene::update(const std::string& input) {
		if (input == "") return input;
		// MeCab
		MeCab::Tagger* tagger = MeCab::createTagger("");
		const std::string result = tagger->parse(input.c_str());
		std::pair<WordList, CategoryListPair> converted_result = convertMecabResult(result);
		return result;
	}
}
