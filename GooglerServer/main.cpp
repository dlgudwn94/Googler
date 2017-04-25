#include "ServerManager.h"
#include <thread>

void RecvStart(ServerManager* a) {
	a->FileRecvStart();
}

int main(void) {
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
	return 0;

}