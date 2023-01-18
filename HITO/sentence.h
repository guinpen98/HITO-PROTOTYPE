#ifndef HITO_SENTENCE_H
#define HITO_SENTENCE_H

namespace HITO {
	using StringList = std::vector<std::string>;

	class Sentence {
	private:
		StringList word_list;
		StringList category1;
		StringList category2;
		int num;

		void deleteAdverb();

	public:
		Sentence(StringList word_list, StringList category1, StringList category2, int num) : word_list(word_list), category1(category1), category2(category2), num(num) {}
		void preprocess();
		int size();
	};
}

#endif //!HITO_SENTENCE_H
