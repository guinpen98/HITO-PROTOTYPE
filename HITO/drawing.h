#ifndef HITO_DRAW_H
#define HITO_DRAW_H
#include <memory>
#include <array>

#include "human.h"
#include "siv_config.h"
#include "clock.h"

namespace HITO {
	class Drawing {
	private:
		std::array<std::unique_ptr<Texture>, 14> textures;
		std::unique_ptr<Human> human;
		const std::wstring default_cmd = L"/X:1 /W:";
		const std::wstring exe = L"softalk\\SofTalk.exe";
		std::unique_ptr<SivConfig> siv_config;
		String text;
		std::string out_sen;
		std::unique_ptr<Clock> clock;
		bool isEnter(const String& siv_str)const;
		void characterDraw()const;
		void sentenceDraw(std::string& sen);
		void textBoxDraw()const;
	public:
		Drawing() : human(new Human()), siv_config(new SivConfig()), clock(new Clock()) {
			textures[0].reset(new Texture(U"img/human/kuchi1.png"));
			textures[1].reset(new Texture(U"img/human/kuchi2.png"));
			textures[2].reset(new Texture(U"img/human/kuchi3.png"));
			textures[3].reset(new Texture(U"img/human/me1.png"));
			textures[4].reset(new Texture(U"img/human/me2.png"));
			textures[5].reset(new Texture(U"img/human/me3.png"));
			textures[6].reset(new Texture(U"img/human/me4.png"));
			textures[7].reset(new Texture(U"img/human/me5.png"));
			textures[8].reset(new Texture(U"img/human/hidarimayu.png"));
			textures[9].reset(new Texture(U"img/human/migimayu.png"));
			textures[10].reset(new Texture(U"img/human/kao.png"));
			textures[11].reset(new Texture(U"img/human/kubi.png"));
			textures[12].reset(new Texture(U"img/human/dotaimae.png"));
			textures[13].reset(new Texture(U"img/human/dotaiushiro.png"));
		}
		void init()const;
		std::string input();
		void clockDrawing();
		void homeSceneDraw()const;
		void dialogueSceneDraw(std::string& sen);
	};
}
#endif // !HITO_DRAW_H
