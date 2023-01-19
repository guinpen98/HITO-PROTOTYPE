#ifndef HITO_SENTENCE_H
#define HITO_SENTENCE_H

#include <vector>

#include "morpheme.h"

namespace HITO {
	class Sentence {
	private:
		std::vector<Morpheme> morphemes;
		int num;

		void dealUnnecessaryTypes();
		bool isRemove(const std::string& type)const;
		bool isRemove(const std::string& type1, const std::string& type2)const;
		bool isCombine(const std::string& type)const;
		bool isCombine(const std::string& type1, const std::string& type2)const;
	public:
		Sentence(std::vector<Morpheme> morphemes, int num) : morphemes(morphemes), num(num) {}
		bool preprocess();
		int size()const;
		bool isThisType(const std::string type)const;
		std::string getSentence()const;
		std::pair<Sentence, Sentence> splitSentence(const int n)const;
	};
}

#endif // !HITO_SENTENCE_H
