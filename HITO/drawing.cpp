#include <windows.h>
#include "stdafx.h"
#include "drawing.h"

namespace HITO {
	void Drawing::characterDraw() const {
		textures[13]->drawAt(human->dotaiushiro.getX(), human->dotaiushiro.getY());
		textures[11]->drawAt(human->kubi.getX(), human->kubi.getY());
		textures[12]->drawAt(human->dotaimae.getX(), human->dotaimae.getY());
		textures[10]->rotatedAt(Vec2{ textures[10]->size().x / 2, textures[10]->size().y / 2 + 130 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human->kao.getX(), human->kao.getY());
		Texture kuchi_texture;
		switch (int(Scene::Time() * 6) % 4)
		{
		case 0:
			kuchi_texture = *textures[0];
			break;
		case 1:
			kuchi_texture = *textures[2];
			break;
		case 2:
			kuchi_texture = *textures[1];
			break;
		case 3:
			kuchi_texture = *textures[2];
			break;
		}
		kuchi_texture.rotatedAt(Vec2{ kuchi_texture.size().x / 2, kuchi_texture.size().y / 2 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human->kuchi.getX(), human->kuchi.getY());
		Texture me_texture = *textures[3];
		switch (int(Scene::Time() * 70) % 150)
		{
		case 0:
			me_texture = *textures[4];
			break;
		case 1:
			me_texture = *textures[5];
			break;
		case 2:
			me_texture = *textures[6];
			break;
		case 3:
			me_texture = *textures[7];
			break;
		case 4:
			me_texture = *textures[6];
			break;
		case 5:
			me_texture = *textures[5];
			break;
		case 6:
			me_texture = *textures[4];
			break;
		}
		me_texture.rotatedAt(Vec2{ me_texture.size().x / 2 + 3, me_texture.size().y / 2 + 92 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human->me1.getX(), human->me1.getY());
		textures[8]->rotatedAt(Vec2{ textures[8]->size().x / 2 - 53, textures[8]->size().y / 2 + 129 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human->hidarimayu.getX(), human->hidarimayu.getY());
		textures[9]->rotatedAt(Vec2{ textures[9]->size().x / 2 + 60, textures[9]->size().y / 2 + 129 }, Periodic::Sine0_1(10s) * 20_deg - 10_deg).drawAt(human->migimayu.getX(), human->migimayu.getY());
	}

	void Drawing::input(String& text) {
		// 入力を取ってくる
		TextInput::UpdateText(text);
		// エンターが押されているか
		if (!isEnter(text)) return;
		// 入力した内容を音声で出力
		std::wstring message_cmd = default_cmd + text.toWstr();
		ShellExecute(0, 0, exe.c_str(), message_cmd.c_str(), L"", SW_SHOW);
		// MeCab
		/*std::string file_text = text.toUTF8();
		MeCab::Tagger* tagger = MeCab::createTagger("");
		const char* result = tagger->parse(file_text.c_str());*/
		// テキストを削除
		text = U"";
	}

	bool Drawing::isEnter(const String& siv_str)const {
		if (siv_str.size() == 0) return false;
		return char32_t(siv_str.back()) == U'\n';
	}
}
