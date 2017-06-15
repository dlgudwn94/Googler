#ifndef WAITTIME
#define WAITTIME
#include <windows.h>

class Wait
{
public:
	void run(int second)
	{
		Seconds = second;
		counting();
	}
private:
	void counting()
	{
		while (1)
		{
			if (Seconds < 0)break;
			SleepEx(1000, false);
			if (Seconds == 0)break;
			Seconds --;
		}
	}
	int Seconds;
};
#endif