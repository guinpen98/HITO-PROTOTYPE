#include <windows.h>
#include <string>

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
		switch (int(Scene::Time() * 70) % 150) {
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

	void Drawing::sentenceDraw() const {
		siv_config->text_font(Unicode::FromUTF8(out_sen)).draw(20, 60);
	}

	void Drawing::textBoxDraw() const {
		String editing_text = TextInput::GetEditingText(); // 文字入力を取得

		// テキストボックスの描画
		area.draw(ColorF{ 0.3 });
		siv_config->font(text + U'|' + editing_text).draw(area.stretched(-20));
	}

	void Drawing::inputModeDraw() const {
		//String siv_sen = Unicode::FromUTF8(out_sen);
		//std::wstring message_cmd = default_cmd + siv_sen.toWstr();
		//ShellExecute(0, 0, exe.c_str(), message_cmd.c_str(), L"", SW_SHOW); // 音声出力

		characterDraw();
		textBoxDraw();
	}
	void Drawing::outputModeDraw() const {
		characterDraw();
		sentenceDraw();
	}

	std::string Drawing::input() {
		TextInput::UpdateText(text);
		if (!isEnter(text)) return ""; // 未入力

		std::string s_text = text.toUTF8();
		text = U""; // 入力を削除
		return s_text;
	}

	void Drawing::clockDrawing() {
		clock->update();
		String time = (clock->hour < 10 ? U"0" : U"") + ToString(clock->hour) + U"：" + (clock->min < 10 ? U"0" : U"") + ToString(clock->min);
		siv_config->font(time).draw(900, 10);
	}

	void Drawing::homeSceneDraw() const {
		characterDraw();
	}

	void Drawing::setSentence(const std::string& sen) {
		out_sen = sen;
	}

	bool Drawing::isEnter(const String& siv_str)const {
		if (siv_str.size() == 0) return false;
		return char32_t(siv_str.back()) == U'\n';
	}

	void Drawing::init()const {
		Window::Resize(window_w, window_h);
		Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	}
}
