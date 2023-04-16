#if _WIN32 || _WIN64
#include <Windows.h>
#endif // _WIN32 || _WIN64

#include "../include/nlu.h"
#include "../include/sentence.h"

namespace HITO {
#if _WIN32 || _WIN64
	// std::string sjisToUtf8(const std::string sjis) {
	// 	String tmp = Unicode::Widen(sjis);
	// 	return tmp.toUTF8();
	// }
	std::string sjisToUtf8(const std::string sjis) {
		//Unicodeへ変換後の文字列長を得る
		int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, sjis.c_str(), sjis.size() + 1, NULL, 0);
		//必要な分だけUnicode文字列のバッファを確保
		wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
		//ShiftJISからUnicodeへ変換
		MultiByteToWideChar(CP_THREAD_ACP, 0, sjis.c_str(), sjis.size() + 1, bufUnicode, lenghtUnicode);
		//UTF8へ変換後の文字列長を得る
		int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
		//必要な分だけUTF8文字列のバッファを確保
		char* bufUTF8 = new char[lengthUTF8];
		//UnicodeからUTF8へ変換
		WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode + 1, bufUTF8, lengthUTF8, NULL, NULL);
		std::string strUTF8(bufUTF8);
		delete bufUnicode;
		delete bufUTF8;
		return strUTF8;
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
#if _WIN32 || _WIN64
			return sjisToUtf8(keyword);
#else
			return keyword;
#endif // _WIN32 || _WIN64
		}
		sentence.preprocess();
		std::string analysis_result = Analyzer::analyze(sentence);
		if (analysis_result.empty()) return parsing_result;
		Analyzer::semanticAnalysis(analysis_result);
#if _WIN32 || _WIN64
		return sjisToUtf8(analysis_result);
#else
		return analysis_result;
#endif // _WIN32 || _WIN64
	}
}
