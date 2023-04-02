#include "../include/nlu.h"
#include "../include/sentence.h"

namespace HITO {
#if _WIN32 || _WIN64
	std::string sjisToUtf8(const std::string sjis) {
		String tmp = Unicode::Widen(sjis);
		return tmp.toUTF8();
	}
#endif // _WIN32 || _WIN64

	Nlu::Nlu(std::shared_ptr<Analyzer> analyzer) :analyzer(analyzer) {
		
	}

	std::string Nlu::understandingLanguage(const std::string& input) const {
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
