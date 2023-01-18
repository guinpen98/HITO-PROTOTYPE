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
		std::string input = drawing->input();
		std::string sen = dialogue_scene->update(input);
		drawing->dialogueSceneDraw(sen);

		if (SimpleGUI::Button(U"ホーム", Vec2{ 850, 500 }, 200))
			current_scene = GameScene::HOME;
	}
}
