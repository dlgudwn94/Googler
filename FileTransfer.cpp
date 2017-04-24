#include "FileTransfer.h"
#include "md5wrapper.h"

FileTransfer::FileTransfer(string filename, char* sendBuffer)
{
	this->mFileName = filename;
	this->isTransferComplete = false;

	//serialize
	mPacket = (Packet*)sendBuffer;
}

FileTransfer::~FileTransfer()
{
	mFileIfstream.close();
}

int FileTransfer::FileStreamOpen()
{
	mFileIfstream.open(mFileName, ios::in | ios::binary);

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

int FileTransfer::ReadyToPacket()
{
	if (!mFileIfstream.eof())
	{
		mFileIfstream.read(mPacket->dataBuffer, DATA_SIZE);
		mPacket->metaData = mFileIfstream.gcount();
		
		if (mPacket->metaData == DATA_SIZE)
		{
			cout << "Packet size full" << endl;
			mPacket->metaData = -1;

			return 1;
		}

		else
		{
			cout << "Last packet" << endl;
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
	md5_hash = md5.getHashFromFile(this->mFileName);
}