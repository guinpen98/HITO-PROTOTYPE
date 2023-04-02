#include <time.h>

#include "../include/clock.h"

namespace HITO {
	void Clock::update() {
		time_t timer = time(NULL);
		struct tm local_time;
		localtime_s(&local_time, &timer);

		year = local_time.tm_year + 1900;
		month = local_time.tm_mon + 1;
		day = local_time.tm_mday;
		hour = local_time.tm_hour;
		min = local_time.tm_min;
		sec = local_time.tm_sec;
	}
}
