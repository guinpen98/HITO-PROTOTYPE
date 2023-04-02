#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#if _WIN32 || _WIN64
#include <Windows.h>
#endif // _WIN32 || _WIN64
#include "mecab.h"

#include "../include/sentence.h"
#include "../include/analyzer.h"

namespace HITO {
	enum class Type {
		S,
		NP,
		VP,
		N,
		V,
		VA,
		AP,
		PP,
	};
	struct TypeNode {
		Type type;
		TypeNode* type_node1;
		TypeNode* type_node2;
	};
	std::string check(const Sentence& sentence, std::string(*f1)(const Sentence&), std::string(*f2)(const Sentence&), const int n, const std::string name) {
		auto [sentence1, sentence2] = sentence.splitSentence(n);
		std::string output1 = f1(sentence1);
		if (output1.empty()) return output1;
		std::string output2 = f2(sentence2);
		if (output2.empty()) return output2;
		return '(' + name + ' ' + output1 + ' ' + output2 + ')';
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
		std::string output = check(sentence, isN, isPP, sentence.size() - 1, "AP"); // 連体化の確認
		if (!output.empty()) return output;
	
		output = check(sentence, isAP, isAP, 1, "AP");
		if (!output.empty()) return output;

		
		for (int i = 2; i <= sentence.size() - 1; ++i) {
			output = check(sentence, isNP, isV, i, "AP");
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
		if (!output.empty()) return output;

		output = check(sentence, isV, isN, 1, "N");
		if (!output.empty()) return output;

		return std::string();
	}

	std::string isS(const Sentence& sentence) {
		std::string output;

		for (int i = 2; i <= sentence.size() - 1; ++i) {
			output = check(sentence, isNP, isAP, i, "S");
			if (!output.empty()) return output;
		}

		for (int i = 2; i <= sentence.size() - 1; ++i) {
			output = check(sentence, isNP, isN, i, "S");
			if (!output.empty()) return output;
		}

		for (int i = 2; i <= sentence.size() - 2; ++i) {
			output = check(sentence, isNP, isVP, i, "S");
			if (!output.empty()) return output;
		}

		output = isV(sentence);
		if (!output.empty()) return output;

		output = isAP(sentence);
		if (!output.empty()) return output;

		output = isVP(sentence);
		if (!output.empty()) return output;

		output = isN(sentence);
		if (!output.empty()) return output;

		if (sentence.size() < 2) return sentence.getSentence();
		output = check(sentence, isNP, isV, sentence.size() - 1, "S");
		if (!output.empty()) return output;

		if (sentence.size() < 3) return sentence.getSentence();
		output = check(sentence, isNP, isV, sentence.size() - 2, "S");
		if (!output.empty()) return output;

		return std::string();
	}

	std::string Analyzer::parse(const Sentence& sentence) {
		return isS(sentence);
	}

	bool Analyzer::init() {
		{
			std::ifstream ifs("interjections.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				return false;
			}
			while (getline(ifs, str)) {
				int index = (int)str.find(" ");
				std::string key = str.substr(0, index);
				std::string value = str.substr(index + 1);
				interjection_dictionary.push_back(KeyValue{ key, value });
			}
		}
		{
			std::ifstream ifs("affirmation.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				return false;
			}
			while (getline(ifs, str)) {
				affirmation_dictionary.push_back(str);
			}
		}
		{
			std::ifstream ifs("denial.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				return false;
			}
			while (getline(ifs, str)) {
				denial_dictionary.push_back(str);
			}
		}
		return true;
	}

	std::string Analyzer::analyze(const Sentence& sentence) {
		return parse(sentence);
	}

	std::string Analyzer::morphologicalAnalysis(const std::string& input) {
		MeCab::Tagger* tagger = MeCab::createTagger("");
		const std::string result = tagger->parse(input.c_str());
		return result;
	}

	Sentence Analyzer::extractMecabResult(const std::string& result) {
		std::vector<Morpheme> sentence;
		int cnt = 0;

		std::stringstream ss_result(result);
		std::string line;
		while (std::getline(ss_result, line, '\n')) {
#if _WIN32 || _WIN64
			line = utf8ToSjis(line);
#endif // _WIN32 || _WIN64
			int index = (int)line.find("\t");
			std::string word = line.substr(0, index);
			std::string category_clump = line.substr(index + 1);
			if (word == "EOS") break; // 終端の場合

			index = (int)category_clump.find(",");
			std::string type1 = category_clump.substr(0, index);
			category_clump = category_clump.substr(index + 1);
			index = (int)category_clump.find(",");
			std::string type2 = category_clump.substr(0, index);

			sentence.push_back(Morpheme{ word, type1, type2 });
			cnt++;
		}
		return Sentence(sentence, cnt);
	}
	void Analyzer::semanticAnalysis(std::string& parsing_result) {
		if (parsing_result[1] == 'N') {
			parsing_result.pop_back();
			parsing_result.erase(0, 3);
		}
	}

	std::string Analyzer::getKeyword(const Sentence& sentence, bool is_ruled_base = false) const {
		for (int i = 0; i < sentence.size(); ++i) {
			if (!sentence.isThisType("感動詞", i)) continue;
			int index = searchKeyword(sentence.getMorphemes(i));
			if (index == -1) continue;
			if (is_ruled_base) return interjection_dictionary[index].value;
			return interjection_dictionary[index].key;
		}
		return std::string();
	}

	int Analyzer::searchKeyword(const std::string& target) const {
		int left = 0, right = (int)interjection_dictionary.size();
		int center = (int)std::floor((left + right) / 2);
		while (left + 1 < right) {
			center = (int)std::floor((left + right) / 2);
			if (target < interjection_dictionary[center].key) right = center;
			else left = center;
		}
		if (interjection_dictionary[left].key == target) return left;
		else return -1;
	}

	AnswerType Analyzer::closedQuestion(const std::string& input) const {
		std::string word = input;
		word.erase(word.size() - 1);
		bool is_affirmation = searchWord(word, affirmation_dictionary);
		if (is_affirmation) {
			return AnswerType::YER;
		}
		bool is_denial = searchWord(word, denial_dictionary);
		if (is_denial) {
			return AnswerType::NO;
		}
		return AnswerType::OTHER;
	}

	bool Analyzer::searchWord(const std::string& target, const std::vector<std::string> dictionary) const {
		int left = 0, right = (int)dictionary.size();
		int center = (int)std::floor((left + right) / 2);
		while (left + 1 < right) {
			center = (int)std::floor((left + right) / 2);
			if (target < dictionary[center]) right = center;
			else left = center;
		}
		return dictionary[left] == target;
	}

#if _WIN32 || _WIN64
	// std::string utf8ToSjis(const std::string utf8) {
	// 	String tmp = Unicode::FromUTF8(utf8);
	// 	return tmp.narrow();
	// }
	std::string utf8ToSjis(const std::string utf8){
		int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(),utf8.size() + 1, NULL, 0);
		//必要な分だけUnicode文字列のバッファを確保
		wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
		//UTF8からUnicodeへ変換
		MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size() + 1,bufUnicode, lenghtUnicode);
		//ShiftJISへ変換後の文字列長を得る
		int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
		//必要な分だけShiftJIS文字列のバッファを確保
		char* bufShiftJis = new char[lengthSJis];
		//UnicodeからShiftJISへ変換
		WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);
		std::string strSJis(bufShiftJis);
		delete bufUnicode;
		delete bufShiftJis;
		return strSJis;
	}
#endif // _WIN32 || _WIN64
}
