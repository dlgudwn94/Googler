#pragma once

#ifndef __SERVERMANAGER
#define __SERVERMANAGER

#include "Network.h"
#include "filemanage.h"


class ServerManager {
private:
	Network* mNetworkIns;
	FileManage* mFileIns;
	char mRecvBuffer[BUFF_SIZE];

	int mPacketCount = 0;

public:
	ServerManager();
	~ServerManager();

	void FileRecvStart();
};

#endif // ~SERVERMANAGER