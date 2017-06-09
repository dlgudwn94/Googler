#include "IpCheck.h"

IpCheck::IpCheck(string fileName) {
	mStream.open(fileName, ios::in);
	if (!mStream.good()) {
		cout << "IP Check file open fail" << endl;
		exit(1);
	}
	mFileName = fileName;
}

IpCheck::~IpCheck() {
	mStream.close();
}

bool IpCheck::Check(string Ip) {
	string buf;
	while (getline(mStream, buf)) {
		if (Ip == buf)
			return false;
	}
	return true;
}