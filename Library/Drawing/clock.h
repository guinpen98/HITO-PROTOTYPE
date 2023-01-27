#ifndef HITO_CLOCK_H
#define HITO_CLOCK_H

namespace HITO {
	struct Clock {
		int year;
		int month;
		int day;
		int hour;
		int min;
		int sec;
		void update();
	};
}

#endif // !HITO_CLOCK_H
