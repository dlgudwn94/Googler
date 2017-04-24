#include "ServerManager.h"

ServerManager::ServerManager() {
	this->mNetworkIns = new Network(mRecvBuffer, BUFF_SIZE, 8888);
	this->mFileIns = new FileManage(mRecvBuffer);
	//mNetworkIns->ConnectUDP();
	mNetworkIns->ConnectTCP();

}

ServerManager::~ServerManager() {
	delete(mNetworkIns);
	delete(mFileIns);
}

void ServerManager::FileRecvStart() {
	int count = 0;
	
	mNetworkIns->AcceptTCP();
		

	while (true) {

		cout << "Waitting for Recive\n";
		//if (mNetworkIns->RecvToClientUDP() == -1) {
		if (mNetworkIns->RecvToClientTCP() == -1) {
			cout << "ERRER: Packet Recv Fail" << endl;
			exit(1);
		}

		if (mFileIns->RecvPacket()) {
			cout << "ERRER: Can't Create File" << endl;
			exit(1);
		}
		cout << "Recv Packet num : " << count << endl;
		cout << "<- Metadata, isComplete? : " << mFileIns->IsOpen() << endl;
		count++;
	}
		
}