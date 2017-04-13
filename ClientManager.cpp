#include "ClientManager.h"

ClientManager::ClientManager(char *fileName, char *servIP) 
{
	this->mFileIns = new FileTransfer(fileName,servIP);

	mFileIns->IsStartup();
	mFileIns->IsSocket();
	mFileIns->ClientStart();
	mFileIns->StartTransfer();
}

int ClientManager::setFileName(char *fileName)
{
	this->fileName = fileName;
	cout << this->fileName << endl;
	return 0;
}

int ClientManager::setServIP(char *servIP)
{
	this->servIP = servIP;
	cout << this->servIP << endl;
	return 0;
}