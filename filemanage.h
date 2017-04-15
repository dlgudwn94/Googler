#pragma once

#ifndef __FILEMANAGE
#define __FILEMANAGE

#include <iostream>
#include <fstream>
#include <string>

#define BUFF_SIZE (1024)
#define DATA_SIZE (BUFF_SIZE - 5)

class Packet {
public:
	int metaData;
	int dataLength;
	char dataBuffer[DATA_SIZE];
};

using namespace std;

class FileManage {
private:
	char* mRecvBuffer;
	string mFileName;
	fstream mFilefstream;
	char FileOpenFlag;
	Packet mPacket;
	bool isTransferComplete;

	void Deserialization();

public:
	FileManage(char* recvBuffer);
	~FileManage();

	int FileStreamOpen(); // first packet error : -2 , open error : -1
	int UnpackPacket();

	bool isComplete();
};

#endif // !__FILEMANAGE
