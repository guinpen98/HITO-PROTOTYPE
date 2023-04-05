#ifndef HITO_DIALOGUE_SCENE_H
#define HITO_DIALOGUE_SCENE_H

#include <array>
#include <fstream>

#include <dialogue_manager.h>

namespace HITO {
	constexpr int char_size = 256;

	enum class IOMode {
		INPUT
		, OUTPUT
	};

	class DialogueScene{
	public:
		std::unique_ptr<DialogueManager> dialogue_manager;

		explicit DialogueScene() : dialogue_manager(new DialogueManager) {}
		std::string init(){
			bool is_success = dialogue_manager->init();
			if (!is_success) return "no";

			std::ifstream ifs("data.txt");
			std::string str;
			if (ifs.fail()) {
				std::cerr << "Failed to open file." << std::endl;
				dialogue_manager->dialogue_mode = DialogueMode::INIT;
				return init_sentence[init_sentence_num];
				init_sentence_num++;
				return "ok";
			}
			while (getline(ifs, str)) {
				dialogue_manager->data.name = str;
			}
			return "ok";
		}
		std::string update(const std::string& input){
			return dialogue_manager->update(input);
		}
	};
}

#endif // !HITO_DIALOGUE_SCENE_H
