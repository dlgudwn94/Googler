#include "ClientManager.h"

int main(void)
{
	ClientManager* CMIns;

	string protocal;

	cout << "input protocal : ";
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
	return 0;
}