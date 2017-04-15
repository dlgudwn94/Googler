#include "ServerManager.h"
#include <stdlib.h>

int main(void) {
	ServerManager* InsSM;

	InsSM = new ServerManager();
	InsSM->FileRecvStart();

	delete(InsSM);

	system("PAUSE");
	return 0;

}