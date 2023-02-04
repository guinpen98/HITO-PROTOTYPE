#ifndef HITO_NLU_H
#define HITO_NLU_H

#include "analyzer.h"

namespace HITO {
	std::string sjisToUtf8(const std::string sjis);

	class Nlu {
	private:
		std::shared_ptr<Analyzer> analyzer;
	public:
		explicit Nlu(std::shared_ptr<Analyzer> analyzer);
		std::string UnderstandingLanguage(const std::string& input);
	};
}

#endif // !HITO_NLU?H
