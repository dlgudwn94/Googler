#ifndef __IPCHECK__
#define __IPCHECK__
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class IpCheck {
private:
	ifstream mStream;
	string mFileName;

public:
	IpCheck(string fileName);
	~IpCheck();
	bool Check(string Ip);
};

#endif