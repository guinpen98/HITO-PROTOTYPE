#ifndef HITO_PART_H
#define HITO_PART_H
class Part
{
private:
	const Texture texture;
	const int x;
	const int y;
	float angle{};

public:
	Part(const char32_t* texture_string, const int new_x, const int new_y) : x(new_x), y(new_y), texture(texture_string)
	{

	};
	int getX()const;
	int getY()const;
	Texture getTexture()const;
	void setAngle(const float new_angle);
	float getAngle()const;
};

#endif //!HITO_PART_H
