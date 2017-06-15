#define _CRT_SECURE_NO_WARNINGS

#include "ServerManager.h"
#include <thread>
#include <iostream>

using namespace std;

void RecvStart(ServerManager* a) {
	a->FileRecvStart();
}
void AddFilter() {
	fstream fs;
	fs.open("IPCheck.txt", ios::_Noreplace | ios::_Nocreate | ios::in);
	if (!fs.is_open()) {
		fs.open("IPCheck.txt", ios::trunc | ios::out);
		fs.close();
	}
	extFilter ef;
	string st;
	char tmp[51];
	cout << "Write filename-extension filter" << endl;
	cout << "empty to start Server" << endl;
	cout << "ex) jpg" << endl;
	while (1) {
		cout << "Filter: ";
		cin.getline(tmp, 50);
		if (strcmp(tmp, "\0") == 0)break;
		st.clear();
		st.append(tmp);
		ef.addFilter(st);
		ef.showFilter();
	}
}

#define BUFSIZE (1024*32)

int main(void) {

	AddFilter();

	ServerManager InsSMUDP(UDP, 8888);
	ServerManager InsSMTCP(TCP, 9999);

	thread t1(RecvStart, &InsSMUDP);
	thread t2(RecvStart, &InsSMTCP);
	t1.join();
	t2.join();

	
	/*
	FILE* file;

	char buf[BUFSIZE];
	Network net(buf, BUFSIZE, 8888);

	net.ConnectTCP();
	net.AcceptTCP();

	file = fopen("2.mkv", "wb");
	if (file == NULL)
		cout << "openerror" << endl;

	int Data_Len;
	while ((Data_Len = net.RecvToClientTCP()) != 0)
		fwrite(buf, sizeof(char), Data_Len, file);

	fclose(file);

	net.~Network();
	*/
	return 0;

}