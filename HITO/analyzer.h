#ifndef HITO_ANALYZER_H
#define HITO_ANALYZER_H

namespace HITO {
	class Analyzer {
	private:
		static void parse();
	public:
		static void analyze(const class Sentence& sen);
	};
}

#endif // !HITO_ANALYZER_H
