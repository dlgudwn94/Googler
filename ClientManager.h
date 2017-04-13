#ifndef __CLIENTMANAGER
#define __CLIENTMANAGER

#include "fileTransfer.h"

#define BUFF_SIZE (1024)

class ClientManager
{
private:
	FileTransfer* mFileIns;
	char *fileName;
	char *servIP;

public:
	ClientManager(char *fileName, char *servIP);
	~ClientManager();
	
	int setFileName(char *fileName);
	int setServIP(char *servIP);
};

#endif