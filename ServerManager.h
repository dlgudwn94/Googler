#pragma once

#ifndef __SERVERMANAGER
#define __SERVERMANAGER

#include "server.h"
#include "filemanage.h"


class ServerManager {
private:
	int RecvFlg;
	Server* mServerIns;
	FileManage* mFileIns;
	char mRecvBuffer[BUFF_SIZE];


public:
	ServerManager();
	~ServerManager();

	void FileRecvStart();
};

#endif // ~SERVERMANAGER