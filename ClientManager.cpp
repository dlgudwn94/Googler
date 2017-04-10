#include "ClientManager.h"

ClientManager::ClientManager() 
{
	this->mFileIns = new FileTransfer();

	mFileIns->IsStartup();
	mFileIns->IsSocket();
	mFileIns->ClientStart();
	mFileIns->StartTransfer();

}
/*
ClientManager::~ClientManager() {
	mNetworkIns->~Network();
	mFileIns->~FileTransfer();
}
*/
