#ifndef HITO_MORPHEME_H
#define HITO_MORPHEME_H

#include <string>

namespace HITO {
	struct Morpheme {
		std::string word;
		std::string type1;
		std::string type2;
	};
}

#endif // !HITO_MORPHEME_H