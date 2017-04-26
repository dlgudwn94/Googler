#ifndef __FILETRANSFER
#define __FILETRANSRFER

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <string>

#define BUFF_SIZE (1024 * 32)
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
	string src;
	ifstream mFileIfstream;
	Packet *mPacket;
	string md5_hash;
	string str_sd;
	bool isTransferComplete;

public:
	FileTransfer(string fileName, char* sendBuffer);
	~FileTransfer();

	//char *srcFileName;
	char *tmp;
	int SetFile();
	int FileStreamOpen();
	int FileStreamClose();
	int ReadyToPacket();
	int ReadyToFolderPacket();
	void getMd5();
	void makeZip();
	bool isComplete();
};

#endif // !__FILETRANSFER
