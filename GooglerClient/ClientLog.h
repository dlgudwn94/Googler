#ifndef __CLIENTLOG
#define __CLIENTLOG

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Log
{
private:
	ofstream f;
	string getFileName;
	string getIp;
	const string currentDate();

public:
	Log(string fileName, string ip);
	~Log();

	void writeLog();
};

#endif // !__CLIENTLOG