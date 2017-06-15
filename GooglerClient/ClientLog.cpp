#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <ctime>
#include "ClientLog.h"

Log::Log(string fileName, string ip)
{
	this->getFileName = fileName;
	this->getIp = ip;
}

const string Log::currentDate()
{
	/*time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	return buf;*/
	time_t now = time(0);
	char *dt = ctime(&now);

	return dt;
}

void Log::writeLog()
{	
	ofstream f("log.txt", ios::app);

	if (f.is_open()) {
		f << this->currentDate();
		f << "IP: " << this->getIp << endl;
		f << "File name: " << this->getFileName << endl << endl;
	}
}

Log::~Log()
{
	f.close();
}