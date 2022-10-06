# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "human.h"
#include "draw.h"
#include <windows.h>


void Main()
{
	wchar_t exe[] = L"C:\\Users\\yuri_\\Downloads\\stn019363\\softalk\\SofTalk.exe";
	wchar_t param[] = L"/X:1 /W:こんにちは";
	ShellExecute(0, 0, exe, param, L"", SW_SHOW);

	Window::Resize(512, 512);

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 通常のフォントを作成 | Create a new font
	const Font font{ 60 };

	// 絵文字用フォントを作成 | Create a new emoji font
	const Font emojiFont{ 60, Typeface::ColorEmoji };

	// `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
	font.addFallback(emojiFont);

	// 画像ファイルからテクスチャを作成 | Create a texture from an image file
	Human human;
	Draw draw;

	double time = 0;

	while (System::Update())
	{
		time += Scene::DeltaTime();
		if (int(time) == 10) {
			ShellExecute(0, 0, exe, param, L"", SW_SHOW);
			time = 0;
		}

		// テクスチャを描く | Draw a texture
		//human.draw();
		draw.characterDraw(human);

		// テキストを画面の中心に描く | Put a text in the middle of the screen
		//font(U"Hello, Siv3D!🚀").drawAt(Scene::Center(), Palette::Black);

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
