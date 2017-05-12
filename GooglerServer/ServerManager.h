#pragma once

#ifndef __SERVERMANAGER
#define __SERVERMANAGER

#include "Network.h"
#include "filemanage.h"

#define UDP 0
#define TCP 1

class ServerManager {
private:
	Network* mNetworkIns;
	FileManage* mFileIns;
	char mRecvBuffer[BUFF_SIZE];

	void FileRecvStartUDP();
	void FileRecvStartTCP();

	int mProtocal;

public:
	ServerManager(int protocal, int port);
	~ServerManager();

	void FileRecvStart();
};

#endif // ~SERVERMANAGER