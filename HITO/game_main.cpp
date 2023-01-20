#include "stdafx.h"
#include "game_main.h"

namespace HITO {
	void GameMain::update() {
		drawing->clockDrawing();
		switch (current_scene) {
		case GameScene::HOME:
			homeScene();
			break;
		case GameScene::DIALOGUE:
			dialogueScene();
			break;
		default:
			break;
		}
	}

	void GameMain::homeScene() {
		home_scene->update();
		drawing->homeSceneDraw();

		if (SimpleGUI::Button(U"対話", Vec2{ 850, 500 }, 200))
			current_scene = GameScene::DIALOGUE;
	}

	void GameMain::dialogueScene() {
		Mode current_mode = dialogue_scene->getMode();
		if (current_mode == Mode::INPUT) {
			std::string input = drawing->input();
			if (input != "") {
				std::string sen = dialogue_scene->generateSentence(input);
				drawing->setSentence(sen);
				dialogue_scene->setOutputMode();
			}
			drawing->inputModeDraw();
		}
		else {
			dialogue_scene->update();
			drawing->outputModeDraw();
		}
		if (SimpleGUI::Button(U"ホーム", Vec2{ 850, 500 }, 200))
			current_scene = GameScene::HOME;
	}
}
