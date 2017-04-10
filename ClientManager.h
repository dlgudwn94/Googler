#pragma once
#include "ClientManager.h"

#ifndef __CLIENTMANAGER
#define __CLIENTMANAGER

#include "Network.h"
#include "fileTransfer.h"

#define BUFF_SIZE (1024)

class ClientManager
{
private:
	Network* mNetworkIns;
	FileTransfer* mFileIns;

public:
	ClientManager();
	~ClientManager();
};

#endif