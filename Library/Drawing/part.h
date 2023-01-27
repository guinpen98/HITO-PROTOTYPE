#ifndef HITO_PART_H
#define HITO_PART_H

namespace HITO {
	class Part
	{
	private:
		const int x;
		const int y;
		float angle{};

	public:
		Part(const int new_x, const int new_y) : x(new_x), y(new_y)
		{};
		int getX()const;
		int getY()const;
		void setAngle(const float new_angle);
		float getAngle()const;
	};
}

#endif //!HITO_PART_H
