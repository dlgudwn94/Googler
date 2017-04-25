#include "FileTransfer.h"
#include "md5wrapper.h"
#include "zlib\Zipper.h"
#include <Windows.h>
FileTransfer::FileTransfer(string filename, char* sendBuffer)
{
	this->mFileName = filename;
	this->isTransferComplete = false;
	char getdir[MAX_PATH];
	src = "";
	GetCurrentDirectory(MAX_PATH, getdir);
	src.append(getdir);
	src.append("\\");
	//serialize
	mPacket = (Packet*)sendBuffer;
}

FileTransfer::~FileTransfer()
{
	mFileIfstream.close();
}

int FileTransfer::FileStreamOpen()
{
	makeZip();

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
	md5_hash = md5.getHashFromFile(mFileName.c_str());
}

void FileTransfer::makeZip()
{
	bool bSrcIsDirectory, br;
	DWORD fileAttr;
	int tmp;
	bSrcIsDirectory = ((fileAttr = GetFileAttributes((src+mFileName).c_str())) & FILE_ATTRIBUTE_DIRECTORY) > 0;
	
	if (fileAttr == 0xFFFFFFFF)
	{
		cout<<"file not exist or has unknown problems"<<endl;
		exit(0);
	}
	
	else
	{
		// 디렉토리인 경우
		if (bSrcIsDirectory)
			br = CZipper::ZipFolder((src + mFileName).c_str(), FALSE);

		// 파일인 경우
		else
			br = CZipper::ZipFile((src + mFileName).c_str());
		if (br) {
			cout <<  "compression completed." << endl;
			tmp = mFileName.find_last_of(".");
			mFileName = mFileName.substr(0, tmp);
			mFileName.append(".zip");
		}
		else {
			cout << "error occured." << endl;
		}
	}
}