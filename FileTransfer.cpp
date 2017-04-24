#include "FileTransfer.h"
#include "md5wrapper.h"
#include "zlib\Zipper.h"

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
	makeZip();

	mFileIfstream.open(srcFileName, ios::in | ios::binary);

	if (! mFileIfstream.is_open())
	{
		cout << "ERROR: Open fail" << endl;
		
		return -1;
	}

	// first packet
	mPacket->metaData = -2;
	strcpy(mPacket->dataBuffer, srcFileName);
	
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
	md5_hash = md5.getHashFromFile(srcFileName);
}

void FileTransfer::makeZip()
{
	bool bSrcIsDirectory, br;
	DWORD fileAttr;

	srcFileName = (char *)malloc(sizeof(char) * 100);

	printf("malloc\n");

	this->srcFileName = "C:\\Users\\IS-3\\Documents\\Project1\\Debug\0";

	printf("경로\n");

	this->tmp = new char[mFileName.size() +1];
	copy(mFileName.begin(), mFileName.end(), tmp);
	tmp[mFileName.size()] = '\0';

	printf("tmp\n");

	strcat(srcFileName, tmp);

	printf("strcat\n");

	bSrcIsDirectory = ((fileAttr = GetFileAttributes(srcFileName)) & FILE_ATTRIBUTE_DIRECTORY) > 0;
	
	if (fileAttr == 0xFFFFFFFF)
	{
		printf("file not exist or has unknown problems");
		exit(0);
	}
	
	else
	{
		// 디렉토리인 경우
		if (bSrcIsDirectory)
			br = CZipper::ZipFolder(srcFileName, FALSE);

		// 파일인 경우
		else
			br = CZipper::ZipFile(srcFileName);

		cout << (br ? "compression completed." : "error occured.") << endl;
	}
}