#ifndef HITO_WORD_H
#define HITO_WORD_H

namespace HITO {
	using StringList = std::vector<std::string>;

	struct Word {
		StringList word_list;
		StringList category1;
		StringList category2;

		Word(StringList word_list, StringList category1, StringList category2) : word_list(word_list), category1(category1), category2(category2) {}
	};
}

#endif //!HITO_WORD_H
