#ifndef HITO_NLU_H
#define HITO_NLU_H

#include "analyzer.hpp"

namespace HITO {
	class Nlu {
	private:
		std::shared_ptr<Analyzer> analyzer;
	public:
		explicit Nlu(std::shared_ptr<Analyzer> analyzer) :analyzer(analyzer) { }
			std::string understandingLanguage(const std::string& input)const {
			std::string parsing_result = Analyzer::morphologicalAnalysis(input);
			Sentence sentence = Analyzer::extractMecabResult(parsing_result);
			std::string keyword = analyzer->getKeyword(sentence, true);
			if (!keyword.empty()) {
				// ルールベースの会話
				std::string rule_based_sen;
				return keyword;
			}
			sentence.preprocess();
			std::string analysis_result = Analyzer::analyze(sentence);
			if (analysis_result.empty()) return parsing_result;
			Analyzer::semanticAnalysis(analysis_result);
			return analysis_result;
		}
	};
}

#endif // !HITO_NLU?H
