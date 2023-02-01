#include<fstream>

#include "game_main.h"

namespace HITO {
	GameMain::GameMain() : drawing(new Drawing), home_scene(new HomeScene), dialogue_scene(new DialogueScene) {
		
	}

	bool GameMain::init() {
		bool is_success = dialogue_scene->init();
		if (dialogue_scene->getOutputSentence() != "") {
			drawing->setSentence(dialogue_scene->getOutputSentence());
			drawing->setOutputTimer();
			dialogue_scene->setOutputMode();
		}
		return is_success;
	}

	void GameMain::update() {
		drawing->clockDrawing();
		if (SimpleGUI::Button(U"セーブ", Vec2{ 100, 100 }, 200))
			saveData();
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

		if (SimpleGUI::Button(U"対話", Vec2{ 900, 500 }, 200))
			current_scene = GameScene::DIALOGUE;
	}

	void GameMain::dialogueScene() {
		IOMode current_mode = dialogue_scene->getMode();
		switch (current_mode) {
		case HITO::IOMode::INPUT:
			inputMode();
			break;
		case HITO::IOMode::OUTPUT:
			outputMode();
			break;
		default:
			break;
		}
		if (SimpleGUI::Button(U"ホーム", Vec2{ 900, 500 }, 200))
			current_scene = GameScene::HOME;
	}
	void GameMain::inputMode() {
		std::string input = drawing->input();
		if (input == "") drawing->inputModeDraw();
		else switchOutputMode(input);
	}
	void GameMain::outputMode() {
		bool is_switch = drawing->outputModeDraw();
		if (is_switch) dialogue_scene->setInputMode();
	}
	void GameMain::switchOutputMode(const std::string& input) {
		std::string sen = dialogue_scene->update(input);
		drawing->setSentence(sen);
		drawing->setOutputTimer();
		dialogue_scene->setOutputMode();
		drawing->outputModeDraw();
	}
	void GameMain::saveData()const {
		std::ofstream outputfile("data.txt");
		outputfile << dialogue_scene->data.name;
		outputfile.close();
	}
}
