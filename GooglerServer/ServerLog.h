#ifndef __SERVERLOG
#define __SERVERLOG

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
	Log(string fileName);
	~Log();
	void writeLog();
};

#endif // !__SERVERLOG