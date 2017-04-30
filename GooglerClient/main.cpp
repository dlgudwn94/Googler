#define _CRT_SECURE_NO_WARNINGS

#include "ClientManager.h"

#define BUFSIZE (1024*32)

int main(void)
{
	/*
	ClientManager* CMIns;

	string protocal;

	cout << "input protocal (TCP,UDP) : ";
	cin >> protocal;
	cin.ignore();

	if(protocal == "UDP")
		CMIns = new ClientManager(UDP, 8888);
	else if(protocal == "TCP")
		CMIns = new ClientManager(TCP, 9999);
	else {
		cout << "ERROR: protocal wrong" << endl;
		return -1;
	}
	CMIns->FileSendStart();

	delete(CMIns);
	*/
	FILE* file;

	char buf[BUFSIZE];
	Network net(buf, BUFSIZE, 8888, "211.33.5.202");
	net.ConnectTCP();

	cout << "file open" << endl;
	file = fopen("2.mkv", "rb");

	int File_len;
	while (true) {
		File_len = fread(buf, sizeof(char), BUFSIZE, file);
		net.SendToDstTCP(File_len);
		if (feof(file))
			break;
	}

	fclose(file);
	net.~Network();


	return 0;
}