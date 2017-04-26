#include "ServerManager.h"

ServerManager::ServerManager(int prococal, int port) {
	this->mNetworkIns = new Network(mRecvBuffer, BUFF_SIZE, port);
	this->mFileIns = new FileManage(mRecvBuffer);
	this->mProtocal = prococal;

	cout << "Server Init ..." << endl;
}

ServerManager::~ServerManager() {
	delete(mNetworkIns);
	delete(mFileIns);
}

void ServerManager::FileRecvStart() {
	if (mProtocal == UDP)
		FileRecvStartUDP();
	else if (mProtocal == TCP)
		FileRecvStartTCP();
	else {
		cout << "ERROR: wrong Protocal" << endl;
		exit(1);
	}
}

void ServerManager::FileRecvStartTCP() {
	
	mNetworkIns->ConnectTCP();

	cout << "TCP Recv Stand by" << endl;

	mNetworkIns->AcceptTCP();
		
	//time
	DWORD t = GetTickCount();
	int count = 1;
	//time end
	
	while (true) {

		//time
		if (GetTickCount() - t >= 1000) {
			cout << " transmission time : " << (count * STRUCT_SIZE)
				<< " byte/sec" << endl;
			t = GetTickCount();
			count = 0;
		}
		//time end

		cout << "Waitting for Recive\n";
		if (mNetworkIns->RecvToClientTCP() == -1) {
			cout << "ERRER: Packet Recv Fail" << endl;
			exit(1);
		}
		count++;	
		
		if(mFileIns->RecvPacket()) {
			cout << "ERRER: Can't Create File" << endl;
			exit(1);
		}
		//cout << "Recv Packet num : " << count << endl;
		//cout << "<- Metadata, isComplete? : " << mFileIns->IsOpen() << endl;
	}
		
}

void ServerManager::FileRecvStartUDP() {

	mNetworkIns->ConnectUDP();

	cout << "UDP Recv Stand by" << endl;

	//time
	DWORD t = GetTickCount();
	int count = 1;
	//time end

	while (true) {

		//time
		if (GetTickCount() - t >= 1000) {
			cout << " transmission time : " << (count * STRUCT_SIZE)
				<< " byte/sec" << endl;
			t = GetTickCount();
			count = 0;
		}
		//time end

		cout << "Waitting for Recive\n";
		if (mNetworkIns->RecvToClientUDP() == -1) {
			cout << "ERRER: Packet Recv Fail" << endl;
			exit(1);
		}
		count++;

		if (mFileIns->RecvPacket()) {
			cout << "ERRER: Packet Read Fail" << endl;
			exit(1);
		}
		//cout << "Recv Packet num : " << count << endl;
		//cout << "<- Metadata, isComplete? : " << mFileIns->IsOpen() << endl;
	}

}