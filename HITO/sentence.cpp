﻿#include <Array>

#include "stdafx.h"
#include "sentence.h"

namespace HITO {
	const std::array<std::string, 7> remove_types = { "副詞", "接続詞", "感動詞", "記号", "フィラー", "その他", "未知語" };
	const std::array<std::string, 2> combine_types = { "連体詞", "接頭詞" };

	void Sentence::dealUnnecessaryTypes() {
		for (int i = 0; i < size(); ++i) {
			if (isRemove(morphemes[i].type1)) {
				morphemes.erase(morphemes.begin() + i);
				--i;
				--num;
			}
			else if (isCombine(morphemes[i].type1)) {
				morphemes[i + 1].word = morphemes[i].word + morphemes[i + 1].word; // 結合
				morphemes.erase(morphemes.begin() + i);
				--i;
				--num;
			}
		}
	}

	void Sentence::dealCompoundNoun() {
		for (int i = 0; i < size() - 1; ++i) {
			if (morphemes[i].type1 != "名詞") continue;
			if (morphemes[i + 1].type1 != "名詞") continue;
			morphemes[i + 1].word = morphemes[i].word + morphemes[i + 1].word; // 結合
			morphemes.erase(morphemes.begin() + i);
			--i;
			--num;
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
		dealCompoundNoun();
		return false;
	}

	int Sentence::size()const {
		return num;
	}

	bool Sentence::isThisType(const std::string type)const {
		if (num != 1) return false;
		return morphemes[0].type1 == type || morphemes[0].type2 == type;
	}

	std::string Sentence::getSentence() const{
		std::string sentence = "";
		for (int i = 0; i < num; ++i) {
			sentence += morphemes[i].word;
		}
		return sentence;
	}
	std::pair<Sentence, Sentence> Sentence::splitSentence(const int n)const {
		std::vector<Morpheme> morphemes1(n), morphemes2(size() - n);
		std::copy(morphemes.begin(), morphemes.begin() + n, morphemes1.begin());
		std::copy(morphemes.begin() + n, morphemes.end(), morphemes2.begin());
		return { Sentence{ morphemes1, n }, Sentence{ morphemes2, size() - n } };
	}
}
