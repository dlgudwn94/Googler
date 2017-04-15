#ifndef __FILETRANSFER
#define __FILETRANSFER

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <string>

#define BUFF_SIZE (1024)
#define DATA_SIZE (BUFF_SIZE - 4)

class Packet
{
public:
	int metaData;
	char dataBuffer[DATA_SIZE];
};

using namespace std;

class FileTransfer
{
private:
	string mFileName;
	ifstream mFileIfstream;
	Packet *mPacket;
	
	bool isTransferComplete;

public:
	FileTransfer(string fileName, char* sendBuffer);
	~FileTransfer();

	int FileStreamOpen();
	int ReadyToPacket();
	bool isComplete();
};

#endif // !__FILETRANSFER
