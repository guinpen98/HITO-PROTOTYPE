#ifndef HITO_DRAW_H
#define HITO_DRAW_H
#include <memory>
#include <array>
#include "human.h"

class Draw
{
private:
	std::array<std::unique_ptr<Texture>, 14> textures;
public:
	Draw() {
		textures[0].reset(new Texture(U"img/human/kuchi.png"));
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
	void characterDraw(Human human)const;
};
#endif //!HITO_DRAW_H
