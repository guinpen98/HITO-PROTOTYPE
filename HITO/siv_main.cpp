﻿#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include <fstream>
#include <string>
#include <iostream>

#include "oav_to_sen.h"
#include "human.h"
#include "drawing.h"
#include "game_main.h"

const std::string file_name = "word.txt";

void writeFile(const std::string& text) {
	std::ofstream writing_file;
	writing_file.open(file_name, std::ios::app);
	writing_file << text << std::endl;
	writing_file.close();
}

void Main() {
	std::unique_ptr<HITO::GameMain> game_main(new HITO::GameMain);

	// OAV
	/*OAVToSEN oav_to_sen("OAV.dat", 1);
	String gen_sen = Unicode::Widen(oav_to_sen.getSen());*/

	std::unique_ptr<HITO::Drawing> drawing(new HITO::Drawing);
	drawing->init();

	GameScene game_scene = GameScene::HOME;

	while (System::Update()) {
		// ボタン
		switch (game_scene) {
		case GameScene::HOME:
			if (SimpleGUI::Button(U"対話", Vec2{ 100, 250 }, 200)) {
				game_scene = GameScene::DIALOGUE;
			}
			drawing->homeSceneDraw();
			break;
		case GameScene::DIALOGUE:
			if (SimpleGUI::Button(U"ホーム", Vec2{ 100, 250 }, 200)) {
				game_scene = GameScene::HOME;
			}
			// キーボードからテキストを入力
			drawing->input();

			// ゲームシステム
			game_main->scene_list[0]->main();

			// 描画
			drawing->dialogueSceneDraw();
			break;
		default:
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/tutorial/
//
// Tutorial
// https://siv3d.github.io/tutorial/tutorial/
//
// Siv3D コミュニティへの参加（Discord などで気軽に質問や交流, 最新情報の入手ができます）
// https://siv3d.github.io/ja-jp/community/community/
//
// Siv3D User Community
// https://siv3d.github.io/community/community/
//
// 新機能の提案やバグの報告 | Feedback
// https://siv3d.github.io/ja-jp/develop/report/
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
