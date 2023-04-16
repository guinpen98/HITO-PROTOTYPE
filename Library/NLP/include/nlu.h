#ifndef HITO_NLU_H
#define HITO_NLU_H

#include "analyzer.h"

namespace HITO {
#if _WIN32 || _WIN64
	std::string sjisToUtf8(const std::string sjis);
#endif // _WIN32 || _WIN64

	class Nlu {
	private:
		std::shared_ptr<Analyzer> analyzer;
	public:
		explicit Nlu(std::shared_ptr<Analyzer> analyzer);
		std::string understandingLanguage(const std::string& input)const;
	};
}

#endif // !HITO_NLU_H