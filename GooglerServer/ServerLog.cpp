#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <ctime>
#include "ServerLog.h"

Log::Log(string fileName)
{
	this->getFileName = fileName;
}

const string Log::currentDate()
{
	time_t now = time(0);
	char *dt = ctime(&now);

	return dt;
}

void Log::writeLog()
{
	ofstream f("log.txt", ios::app);

	if (f.is_open()) {
		f << this->currentDate();
		f << "File name: " << this->getFileName << endl << endl;
	}
}

Log::~Log()
{
	f.close();
}