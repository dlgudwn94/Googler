#define _CRT_SECURE_NO_WARNINGS

#include "ServerManager.h"
#include <thread>
#include <iostream>

using namespace std;

void RecvStart(ServerManager* a) {
	a->FileRecvStart();
}

#define BUFSIZE (1024*32)

int main(void) {
	/*
	ServerManager* InsSMUDP;
	ServerManager* InsSMTCP;


	InsSMUDP = new ServerManager(UDP, 8888);
	InsSMTCP = new ServerManager(TCP, 9999);

	thread t1(RecvStart, InsSMUDP);
	thread t2(RecvStart, InsSMTCP);
	t1.join();
	t2.join();

	delete(InsSMTCP);
	delete(InsSMUDP);
	*/
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
	
	return 0;

}