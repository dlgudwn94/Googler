#include "ServerManager.h"

int main(void) {
	ServerManager* InsSM;
	char* fileName;

	InsSM = new ServerManager();
	InsSM->FileRecvStart();

	return 0;

}