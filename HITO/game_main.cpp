#include "stdafx.h"
#include "game_main.h"

void HITO::GameMain::update() {
	drawing->clockDrawing();
	switch (game_scene) {
	case GameScene::HOME:
		scene_list[int(game_scene)]->update();
		drawing->homeSceneDraw();

		if (SimpleGUI::Button(U"対話", Vec2{ 100, 250 }, 200))
			game_scene = GameScene::DIALOGUE;
		break;
	case GameScene::DIALOGUE:
		drawing->input();
		scene_list[int(game_scene)]->update();
		drawing->dialogueSceneDraw();

		if (SimpleGUI::Button(U"ホーム", Vec2{ 100, 250 }, 200))
			game_scene = GameScene::HOME;
		break;
	default:
		break;
	}
}
