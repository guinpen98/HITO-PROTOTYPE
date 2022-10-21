#include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "human.h"
#include "draw.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include "mecab.h"

//std::wstring sivStringToWstring(const String siv_str) {
//	std::wstring wstr;
//	for (int i = 0; i < (int)siv_str.size(); ++i) {
//		wstr.push_back(wchar_t(siv_str[i]));
//	}
//	return wstr;
//}
bool isEnter(const String siv_str) {
	if (siv_str.size() == 0) return false;
	return char32_t(siv_str.back()) == U'\n';
}

void Main()
{
	wchar_t exe[] = L"C:\\Users\\yuri_\\Downloads\\stn019363\\softalk\\SofTalk.exe";
	wchar_t param[] = L"/X:1 /W:こんにちは";
	ShellExecute(0, 0, exe, param, L"", SW_SHOW);

	Window::Resize(window_w, window_h);

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Font font{ 40 };

	String text;

	constexpr Rect area{ window_w / 2 - 250, window_h - 200, 500, 160 };

	// 絵文字用フォントを作成 | Create a new emoji font
	const Font emoji_font{ 60, Typeface::ColorEmoji };

	// `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
	font.addFallback(emoji_font);

	// 画像ファイルからテクスチャを作成 | Create a texture from an image file
	Human human;
	Draw draw;

	//double time = 0;

	const std::wstring default_cmd = L"/X:1 /W:";

	// 文字列を受け取った後
	std::wstring message_cmd;

	String editing_text;
	
	std::string file_name = "word.txt";
	std::ofstream writing_file;

	while (System::Update())
	{
		/*time += Scene::DeltaTime();
		if (int(time) == 10) {
			ShellExecute(0, 0, exe, param, L"", SW_SHOW);
			time = 0;
		}*/
		
		// テクスチャを描く | Draw a texture
		draw.characterDraw(human);

		// キーボードからテキストを入力
		TextInput::UpdateText(text);
		if (isEnter(text)) {
			message_cmd = default_cmd + text.toWstr();
			ShellExecute(0, 0, exe, message_cmd.c_str(), L"", SW_SHOW);

			std::string file_text = text.toUTF8();

			MeCab::Tagger* tagger = MeCab::createTagger("-Owakati");
			const char* result = tagger->parse(file_text.c_str());

			writing_file.open(file_name, std::ios::app);
			file_text.pop_back();
			writing_file << file_text << std::endl;
			writing_file << result << std::endl;
			writing_file.close();


			text = U"";
		}
		font(text).draw(20, 20);
		// 未変換の文字入力を取得
		editing_text = TextInput::GetEditingText();

		area.draw(ColorF{ 0.3 });

		font(text + U'|' + editing_text).draw(area.stretched(-20));

		// マウスカーソルに追随する半透明な円を描く | Draw a red transparent circle that follows the mouse cursor
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
