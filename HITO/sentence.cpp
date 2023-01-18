#include <Array>

#include "stdafx.h"
#include "sentence.h"

namespace HITO {
	const std::array<std::string, 7> remove_types = { "副詞", "接続詞", "感動詞", "記号", "フィラー", "その他", "未知語" };
	const std::array<std::string, 2> combine_types = { "連体詞", "接頭詞" };

	void Sentence::dealUnnecessaryTypes() {
		for (int i = 0; i < size(); ++i) {
			if (isRemove(sentence[i].type1)) {
				sentence.erase(sentence.begin() + i);
				--i;
				--num;
			}
			else if (isCombine(sentence[i].type1)) {
				sentence[i + 1].word = sentence[i].word + sentence[i + 1].word; // 結合
				sentence.erase(sentence.begin() + i);
				--i;
				--num;
			}
		}
	}

	bool Sentence::isRemove(const std::string& type) const {
		for (int i = 0; i < remove_types.size(); ++i)
			if (type == remove_types[i]) return true;
		return false;
	}

	bool Sentence::isCombine(const std::string& type) const {
		for (int i = 0; i < combine_types.size(); ++i)
			if (type == combine_types[i]) return true;
		return false;
	}

	bool Sentence::preprocess() {
		dealUnnecessaryTypes();
		return false;
	}

	int Sentence::size()const {
		return num;
	}

	std::vector<std::string> Sentence::getKeywords()const {
		return keywords;
	}
}
