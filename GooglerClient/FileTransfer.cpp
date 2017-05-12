#include "FileTransfer.h"
#include "SearchDirectory.h"
#include "md5wrapper.h"
#include <Windows.h>
//SearchDirectory sd;
FileTransfer::FileTransfer(string filename, char* sendBuffer)
{
	SearchDirectory sd;
	this->mFileName = filename;
	this->isTransferComplete = false;
	char getdir[MAX_PATH];
	src = "";
	GetCurrentDirectory(MAX_PATH, getdir);
	src.append(getdir);
	src.append("\\");
	sd.MakeDirList(src + mFileName);
	str_sd = sd.DirList();
	//serialize
	mPacket = (Packet*)sendBuffer;
}

FileTransfer::~FileTransfer()
{
	mFileIfstream.close();
}

int FileTransfer::SetFile() {
	SearchDirectory sd;
	sd.SetDirList(str_sd);
	mFileName = sd.GetDir();
	str_sd = sd.DirList();
	if (mFileName[1] == 'D') {//디렉토리
		mFileName.erase(0, 2);
		return 0;
	}
	else if (mFileName[1] == 'E') {//파일
		mFileName.erase(0, 2);
		return 2;
	}
	else  {//없음
		return 1;
	}
}

int FileTransfer::FileStreamOpen()
{

	mFileIfstream.open(mFileName.c_str(), ios::in | ios::binary);

	if (! mFileIfstream.is_open())
	{
		cout << "ERROR: Open fail" << endl;
		
		return -1;
	}

	// first packet
	mPacket->metaData = -2;
	strcpy(mPacket->dataBuffer, mFileName.c_str());
	
	return 0;
}

int FileTransfer::FileStreamClose() {
	mFileIfstream.close();
	return 0;
}

int FileTransfer::ReadyToFolderPacket() {
	mPacket->metaData = -4;
	strcpy(mPacket->dataBuffer, mFileName.c_str());
	return 0;
}

int FileTransfer::ReadyToPacket()
{
	if (!mFileIfstream.eof())
	{
		mFileIfstream.read(mPacket->dataBuffer, DATA_SIZE);
		mPacket->metaData = mFileIfstream.gcount();
		
		if (mPacket->metaData == DATA_SIZE)
		{
			//cout << "Packet size full" << endl;
			mPacket->metaData = -1;

			return 1;
		}

		else
		{
			//cout << "Last packet" << endl;
			//isTransferComplete = true;

			return 1;
		}
	}
	
	else // 마지막이 딱 DATA 사이즈였을 경우
	{
		cout << "EOF" << endl;
		//md5 해쉬 보냄
		getMd5();
		mPacket->metaData = -3;
		strcpy_s(mPacket->dataBuffer, md5_hash.size() + 1, md5_hash.c_str());

		isTransferComplete = true;
		FileStreamClose();
		return 0;
	}
}

bool FileTransfer::isComplete()
{
	return isTransferComplete;
}

void  FileTransfer::getMd5()
{
	md5wrapper md5;
	md5_hash = md5.getHashFromFile(mFileName.c_str());
}

