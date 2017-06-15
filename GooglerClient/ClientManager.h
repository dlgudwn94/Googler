#ifndef __CLIENTMANAGER
#define __CLIENTMANAGER

#include "Network.h"
#include "FileTransfer.h"
#include "ClientLog.h"

#define UDP 0
#define TCP 1

class ClientManager
{
private:
	Network* mNetworkIns;
	FileTransfer* mFileIns;
	Log* mLogIns;
	
	char mSendBuffer[BUFF_SIZE];

	void FileSendStartTCP();
	void FileSendStartUDP();

	int mProtocal;
	string mIp;

public:
	ClientManager();
	~ClientManager();

	void FileSendStart();
};

#endif // !__CLIENTMANAGER
