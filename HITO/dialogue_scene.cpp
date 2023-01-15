#include "mecab.h"

#include "stdafx.h"
#include "dialogue_scene.h"

namespace HITO {
	GameScene DialogueScene::update() {
		return GameScene::DIALOGUE;
    }
	std::string DialogueScene::update(std::string& input)
	{
		// MeCab
		MeCab::Tagger* tagger = MeCab::createTagger("");
		const std::string result = tagger->parse(input.c_str());
		return result;
	}
}
