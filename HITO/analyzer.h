#ifndef HITO_ANALYZER_H
#define HITO_ANALYZER_H

namespace HITO {
	class Analyzer {
	private:
		static std::string parse(const class Sentence& sentence);
	public:
		static std::string analyze(const Sentence& sentence);
	};
}

#endif // !HITO_ANALYZER_H
