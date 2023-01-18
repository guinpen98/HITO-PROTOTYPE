#include "stdafx.h"
#include "sentence.h"

void HITO::Sentence::deleteAdverb() {
	for (int i = 0; i < size(); ++i) {
		if (category1[i] == "副詞") {
			word_list.erase(word_list.begin() + i);
			category1.erase(category1.begin() + i);
			category2.erase(category2.begin() + i);
			--i;
			--num;
		}
	}
}

void HITO::Sentence::preprocess() {
	deleteAdverb();
}

int HITO::Sentence::size() {
	return num;
}
