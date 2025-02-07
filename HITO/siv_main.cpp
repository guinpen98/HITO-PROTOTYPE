﻿#include "game_main.h"

const std::string file_name = "word.txt";

//void writeFile(const std::string& text) {
//	std::ofstream writing_file;
//	writing_file.open(file_name, std::ios::app);
//	writing_file << text << std::endl;
//	writing_file.close();
//}

void init() {
	Window::Resize(window_w, window_h);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
}

void Main() {
	init();
	std::unique_ptr<HITO::GameMain> game_main(new HITO::GameMain);

	bool is_success = game_main->init();

	if (!is_success) return;

	/*OAVToSEN oav_to_sen("OAV.dat", 1);
	String gen_sen = Unicode::Widen(oav_to_sen.getSen());*/

	while (System::Update()) {
		game_main->update();
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
