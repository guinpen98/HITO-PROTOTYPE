#ifndef HITO_SENTENCE_H
#define HITO_SENTENCE_H

#include <vector>

#include "morpheme.h"

namespace HITO {
	class Sentence {
	private:
		int num;
		std::vector<Morpheme> sentence;
		std::vector<std::string> keywords;
		void dealUnnecessaryTypes();
		bool isRemove(const std::string& type)const;
		bool isCombine(const std::string& type)const;
	public:
		Sentence(std::vector<Morpheme> sentence, int num) : sentence(sentence), num(num) {}
		bool preprocess();
		int size()const;
		std::vector<std::string> getKeywords()const;
	};
}

#endif // !HITO_SENTENCE_H
