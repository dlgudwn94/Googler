#ifndef __CLIENTMANAGER
#define __CLIENTMANAGER

#include "Network.h"
#include "FileTransfer.h"

class ClientManager
{
private:
	Network* mNetworkIns;
	FileTransfer* mFileIns;
	
	char mSendBuffer[BUFF_SIZE];

public:
	ClientManager();
	~ClientManager();

	void FileSendStart();
};

#endif // !__CLIENTMANAGER
