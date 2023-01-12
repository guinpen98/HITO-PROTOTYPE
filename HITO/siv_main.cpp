#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include <fstream>
#include <string>
#include <iostream>

#include "mecab.h"

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
	// Siv3D
	Window::Resize(window_w, window_h);

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Font font{ 40 };

	String text;

	constexpr Rect area{ window_w / 2 - 250, window_h - 200, 500, 160 };

	std::unique_ptr<HITO::Drawing> drawing(new HITO::Drawing);

	String editing_text;

	// OAV
	OAVToSEN oav_to_sen("OAV.dat", 1);
	String gen_sen = Unicode::Widen(oav_to_sen.getSen());

	// GameMain
	HITO::GameMain game_main;
	game_main.scene_list[0]->main();

	while (System::Update()) {	
		// テクスチャを描く | Drawing a texture
		drawing->characterDraw();

		// キーボードからテキストを入力
		drawing->input(text);

		// OVA
		font(gen_sen).draw(20, 20);

		// 未変換の文字入力を取得
		editing_text = TextInput::GetEditingText();

		area.draw(ColorF{ 0.3 });
		font(text + U'|' + editing_text).draw(area.stretched(-20));

		// マウスカーソルに追随する半透明な円を描く | Drawing a red transparent circle that follows the mouse cursor
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });
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
