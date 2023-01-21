#include "game_main.h"

namespace HITO {
	GameMain::GameMain() : drawing(new Drawing), home_scene(new HomeScene), dialogue_scene(new DialogueScene) {
		// drawing->init();
	}

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
			if (input == "") drawing->inputModeDraw();
			else {
				std::string sen = dialogue_scene->generateSentence(input);
				drawing->setSentence(sen);
				drawing->setOutputTimer();
				dialogue_scene->setOutputMode();
				drawing->outputModeDraw();
			}
		}
		else {
			bool is_switch = drawing->outputModeDraw();
			if (is_switch) dialogue_scene->setInputMode();
		}
		if (SimpleGUI::Button(U"ホーム", Vec2{ 850, 500 }, 200))
			current_scene = GameScene::HOME;
	}
}
