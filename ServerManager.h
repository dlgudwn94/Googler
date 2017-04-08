#pragma once

#ifndef __SERVERMANAGER
#define __SERVERMANAGER

#include "server.h"
#include "filemanage.h"

#define BUFF_SIZE (1024)

class ServerManager {
private:
	Server* mServerIns;
	FileManage* mFileIns;
	char mRecvBuffer[BUFF_SIZE];


public:
	ServerManager(char* createFileName);
	~ServerManager();

	void FileRecvStart();
};

#endif // ~SERVERMANAGER