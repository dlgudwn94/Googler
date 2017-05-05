#define _CRT_SECURE_NO_WARNINGS

#include "ClientManager.h"

#define BUFSIZE (1024*32)

int main(void)
{

	ClientManager CMins(TCP, 9999);
	CMins.FileSendStart();
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
	

	return 0;
}