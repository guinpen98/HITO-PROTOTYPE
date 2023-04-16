#ifndef HITO_ANALYZER_H
#define HITO_ANALYZER_H

#include <string>
#include <vector>

namespace HITO {
	struct KeyValue {
		const std::string key;
		const std::string value;
	};

	enum class AnswerType {
		YER,
		NO,
		OTHER
	};

#if _WIN32 || _WIN64
	std::string utf8ToSjis(const std::string utf8);
#endif // _WIN32 || _WIN64

	class Analyzer {
	private:
		std::vector<KeyValue> interjection_dictionary;
		std::vector<std::string> affirmation_dictionary;
		std::vector<std::string> denial_dictionary;

		bool searchWord(const std::string& target, const std::vector<std::string> dictionary)const;
		int searchKeyword(const std::string& target)const;

		static std::string parse(const class Sentence& sentence);
	public:
		bool init();
		std::string getKeyword(const class Sentence& sentence, bool is_ruled_base)const;
		AnswerType closedQuestion(const std::string& input)const;

		static std::string analyze(const Sentence& sentence);
		static std::string morphologicalAnalysis(const std::string& input);
		static class Sentence extractMecabResult(const std::string& result);
		static void semanticAnalysis(std::string& parsing_result);
	};
}

#endif // !HITO_ANALYZER_H