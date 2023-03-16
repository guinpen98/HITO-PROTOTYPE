#ifndef HITO_SENTENCE_H
#define HITO_SENTENCE_H
#include <array>
#include <cmath>
#include <vector>

#include "morpheme.hpp"

namespace HITO {
	struct TypePair {
		std::string forward;
		std::string backward;
	};

	const std::array<std::string, 7> remove_types = { "副詞", "接続詞", "感動詞", "記号", "フィラー", "その他", "未知語" };
	const std::array<std::string, 2> combine_types = { "連体詞", "接頭詞" };
	const std::array<TypePair, 0> remove_type_pairs = {  };
	const std::array<TypePair, 7> combine_type_pairs = { TypePair{ "名詞", "名詞" }, TypePair{ "助動詞", "助詞" }, TypePair{ "助動詞", "助動詞" }, TypePair{ "動詞", "助詞" },TypePair{ "動詞", "動詞" }, TypePair{ "形容詞", "助動詞" }, TypePair{ "形容詞", "助詞" } };

	class Sentence {
	private:
		std::vector<Morpheme> morphemes;
		int num;

		void dealUnnecessaryTypes() {
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
			for (int i = 0; i < size() - 1; ++i) {
				if (isRemove(morphemes[i].type1, morphemes[i + 1].type1)) {
					morphemes.erase(morphemes.begin() + i + 1);
					--i;
					--num;
				}
				else if (isCombine(morphemes[i].type1, morphemes[i + 1].type1)) {
					morphemes[i].word += morphemes[i + 1].word; // 結合
					morphemes.erase(morphemes.begin() + i + 1);
					--i;
					--num;
				}
			}
		}

		bool isRemove(const std::string& type)const {
			for (int i = 0; i < remove_types.size(); ++i)
				if (type == remove_types[i]) return true;
			return false;
		}

		bool isRemove(const std::string& type1, const std::string& type2)const {
			for (int i = 0; i < remove_type_pairs.size(); ++i)
				if (type1 == remove_type_pairs[i].forward && type2 == remove_type_pairs[i].backward) return true;
			return false;
		}

		bool isCombine(const std::string& type)const {
			for (int i = 0; i < combine_types.size(); ++i)
				if (type == combine_types[i]) return true;
			return false;
		}

		bool isCombine(const std::string& type1, const std::string& type2)const {
			for (int i = 0; i < combine_type_pairs.size(); ++i)
				if (type1 == combine_type_pairs[i].forward && type2 == combine_type_pairs[i].backward) return true;
			return false;
		}

	public:
		explicit Sentence(std::vector<Morpheme> morphemes, int num) : morphemes(morphemes), num(num) {}

		void preprocess() {
			dealUnnecessaryTypes();
		}

		int size()const {
			return num;
		}

		bool isThisType(const std::string type)const {
			if (size() != 1) return false;
			return morphemes[0].type1 == type || morphemes[0].type2 == type;
		}

		bool isThisType(const std::string type, const int index)const {
			if (size() <= index) return false;
			return morphemes[index].type1 == type || morphemes[index].type2 == type;
		}

		std::string getSentence()const {
			std::string sentence = "";
			for (int i = 0; i < size(); ++i) {
				sentence += morphemes[i].word;
			}
			return sentence;
		}

		std::string getMorphemes(const int index)const {
			return morphemes[index].word;
		}

		std::pair<Sentence, Sentence> splitSentence(const int n)const {
			std::vector<Morpheme> morphemes1(n), morphemes2(size() - n);
			std::copy(morphemes.begin(), morphemes.begin() + n, morphemes1.begin());
			std::copy(morphemes.begin() + n, morphemes.end(), morphemes2.begin());
			return { Sentence{ morphemes1, n }, Sentence{ morphemes2, size() - n } };
		}
	};
}

#endif // !HITO_SENTENCE_H
