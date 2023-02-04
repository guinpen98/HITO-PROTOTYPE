#include "nlu.h"
#include "sentence.h"

namespace HITO {
	std::string sjisToUtf8(const std::string sjis) {
		String tmp = Unicode::Widen(sjis);
		return tmp.toUTF8();
	}

	Nlu::Nlu(std::shared_ptr<Analyzer> analyzer) :analyzer(analyzer) {
		
	}

	std::string Nlu::UnderstandingLanguage(const std::string& input) {
		std::string parsing_result = Analyzer::morphologicalAnalysis(input);
		Sentence sentence = Analyzer::extractMecabResult(parsing_result);
		std::string keyword = analyzer->getKeyword(sentence, true);
		if (!keyword.empty()) {
			// ルールベースの会話
			std::string rule_based_sen;
			return sjisToUtf8(keyword);
		}
		sentence.preprocess();
		std::string analysis_result = Analyzer::analyze(sentence);
		if (analysis_result.empty()) return parsing_result;
		Analyzer::semanticAnalysis(analysis_result);
		return sjisToUtf8(analysis_result);
	}
}
