#include "ClientManager.h"

int main(void)
{
	ClientManager* CMIns;

	CMIns = new ClientManager();
	CMIns->FileSendStart();

	delete(CMIns);
	return 0;
}