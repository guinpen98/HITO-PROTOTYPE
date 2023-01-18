#include "stdafx.h"
#include "sentence.h"
#include "analyzer.h"

namespace HITO {
	std::string check(const Sentence& sentence, std::string(*f1)(const Sentence&), std::string(*f2)(const Sentence&), const int n, const std::string name) {
		auto [sentence1, sentence2] = sentence.splitSentence(n);
		std::string output1 = f1(sentence1);
		if (output1.empty()) return output1;
		std::string output2 = f2(sentence2);
		if (output2.empty()) return output2;
		return name + '(' + output1 + ' ' + output2 + ')';
	}

	std::string isV(const Sentence& sentence) {
		if (sentence.size() != 1 && sentence.size() != 2) return std::string();
		if (sentence.size() == 1)
			if (sentence.isThisType("動詞")) return "(V " + sentence.getSentence() + ")";
		if (sentence.size() == 2) {
			auto [sentence1, sentence2] = sentence.splitSentence(1);
			if (sentence1.isThisType("動詞") && sentence2.isThisType("助動詞")) return "(V " + sentence.getSentence() + ")";
		}
		return std::string();
	}

	std::string isVA(const Sentence& sentence) {
		if (sentence.size() != 1) return std::string();
		if (sentence.isThisType("助動詞")) return "(VA " + sentence.getSentence() + ")";
		return std::string();
	}

	std::string isPP(const Sentence& sentence) {
		if (sentence.size() != 1) return std::string();
		if (sentence.isThisType("助詞")) return "(PP " + sentence.getSentence() + ")";
		return std::string();
	}

	std::string isN(const Sentence& sentence);

	std::string isVP(const Sentence& sentence) {
		if (sentence.size() < 2) return std::string();

		std::string output = check(sentence, isN, isVA, sentence.size() - 1, "VP");
		if (!output.empty()) return output;

		//output = check(sentence, isV, isVA, sentence.size() - 1, "VP");
		//if (!output.empty()) return output;

		return std::string();
	}

	std::string isNP(const Sentence& sentence) {
		if (sentence.size() < 2) return std::string();

		std::string output = check(sentence, isN, isPP, sentence.size() - 1, "NP");
		if (!output.empty()) return output;
		return std::string();

	}

	std::string isAP(const Sentence& sentence) {
		if (sentence.size() == 0) return std::string();
		if (sentence.size() == 1) {
			if (sentence.isThisType("形容詞")) return "(AP " + sentence.getSentence() + ")";
			return std::string();
		}
		std::string output = check(sentence, isN, isPP, sentence.size() - 1, "AP");
		if (!output.empty()) return output;
	
		output = check(sentence, isAP, isAP, 1, "AP");
		if (!output.empty()) return output;

		
		for (int i = 2; i <= sentence.size() - 1; i++) {
			output = check(sentence, isNP, isVP, i, "AP");
			if (!output.empty()) return output;
		}
	
		return std::string();
	}

	std::string isN(const Sentence& sentence) {
		if (sentence.size() == 0) return std::string();
		if (sentence.size() == 1) {
			if (sentence.isThisType("名詞")) return "(N " + sentence.getSentence() + ")";
			return std::string();
		}
		std::string output = check(sentence, isAP, isN, sentence.size() - 1, "N");
		if (output.empty()) return std::string();
		else return output;
	}

	std::vector<std::string> isS(const Sentence& sentence) {
		std::vector<std::string> result;
		if (sentence.size() < 3) {
			result.push_back(sentence.getSentence());
			return result;
		}

		std::string output = check(sentence, isNP, isV, sentence.size() - 1, "S");
		if (!output.empty()) result.push_back(output);
		output = check(sentence, isNP, isV, sentence.size() - 2, "S");
		if (!output.empty()) result.push_back(output);

		for (int i = 2; i <= sentence.size() - 1; i++) {
			output = check(sentence, isNP, isAP, i, "S");
			if (!output.empty()) result.push_back(output);
		}

		for (int i = 2; i <= sentence.size() - 2; i++) {
			output = check(sentence, isNP, isVP, i, "S");
			if (!output.empty()) result.push_back(output);
		}

		return result;
	}

	std::vector<std::string> Analyzer::parse(const Sentence& sentence) {
		return isS(sentence);
	}

	std::vector<std::string> Analyzer::analyze(const Sentence& sentence) {
		return parse(sentence);
	}
}
