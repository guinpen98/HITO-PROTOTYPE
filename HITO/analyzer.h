#ifndef HITO_ANALYZER_H
#define HITO_ANALYZER_H

namespace HITO {
	class Analyzer {
	private:
		static std::string parse(const class Sentence& sentence);
	public:
		static std::string analyze(const Sentence& sentence);
		static std::string morphologicalAnalysis(const std::string& input);
		static class Sentence extractMecabResult(const std::string& result);
	};
}

#endif // !HITO_ANALYZER_H
