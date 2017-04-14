#include "ServerManager.h"

int main(void) {
	ServerManager* InsSM;

	InsSM = new ServerManager();
	InsSM->FileRecvStart();

	return 0;

}