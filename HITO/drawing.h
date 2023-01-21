#ifndef HITO_DRAWING_H
#define HITO_DRAWING_H
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
		String out_sen;
		std::unique_ptr<struct Clock> clock;
		std::chrono::system_clock::time_point start;

		bool isEnter(const String& siv_str)const;
		void characterDraw()const;
		bool sentenceDraw(bool isCrawling)const;
		void textBoxDraw()const;
	public:
		explicit Drawing();
		void init()const;
		std::string input();
		void clockDrawing();
		void homeSceneDraw()const;
		void inputModeDraw()const;
		bool outputModeDraw()const; // inputに切り替わるときにtrue
		void setOutputTimer();
		void setSentence(const std::string& sen);
	};
}
#endif // !HITO_DRAWING_H
