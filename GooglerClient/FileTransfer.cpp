#include "FileTransfer.h"
#include "SearchDirectory.h"
#include "md5wrapper.h"
#include <Windows.h>
//SearchDirectory sd;
FileTransfer::FileTransfer(string filename, char* sendBuffer,string ip)
{
	SearchDirectory sd;
	this->mFileName = filename;
	this->isTransferComplete = false;
	isRe = 0;
	char getdir[MAX_PATH];
	src = "";
	GetCurrentDirectory(MAX_PATH, getdir);
	src.append(getdir);
	src.append("\\");
	sd.MakeDirList(src + mFileName);
	str_sd = sd.DirList();
	isRetrans();
	mData.close();
	if (!isRe)sd.MakeListFile(ip);
	mData.open(DATA_FILE_NAME, ios::out | ios::in | ios::binary);
	mData.seekg(0, ios::end);
	dataEnd = mData.tellg();
	mData.seekg(15, ios::beg);
	//serialize
	mPacket = (Packet*)sendBuffer;
}

FileTransfer::~FileTransfer()
{
	mFileIfstream.close();
}

int FileTransfer::SetFile() {
	/*
	SearchDirectory sd;
	sd.SetDirList(str_sd);
	mFileName = sd.GetDir();
	str_sd = sd.DirList();*/

	if (getData(&wp, &mFileName))return 1;
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

int FileTransfer::isRetrans() {
	mData.open(DATA_FILE_NAME, ios::out | ios::in | ios::binary);
	int flg = 1;
	int next, read;
	long long fp = 0;
	char buf[50] = { 0, };
	mData.seekg(0, ios::end);
	dataEnd = mData.tellg();
	mData.seekg(15, ios::beg);
	if (dataEnd == -1)return 1;
	if (mData.eof())return 1;
	do {
		mData.read(buf, 4);
		next = *(int*)buf;
		mData.read(buf, 8);
		fp = *(long long *)buf;
		read = next - mData.tellg();
		mData.read(buf, read);
		if (flg) {
			buf[read] = '\0';
			mFileName.clear();
			mFileName.append(buf);
			flg = 0;
		}
	} while (fp == -2 && (next < dataEnd));
	mData.seekg(15, ios::beg);
	//if (mData.eof())return 1;
	if (fp == -2)return 1;
	isRe = 1;
	wp = fp;
	return 0;
}

int FileTransfer::getData(long long *wp, string *name) {
	char buf[50];
	int read;
	int next = 0;
	long long fp = 0;
	if (-1 == mData.tellg())return 1;
	if (dataEnd == mData.tellg())return 1;
	do {
		mData.read(buf, 4);
		next = *(int*)buf;
		nowData = mData.tellg();
		mData.read(buf, 8);
		fp = *(long long *)buf;
		read = next - mData.tellg();
		mData.read(buf, read);
		buf[read] = '\0';
		cout << "-fileName : " << &buf[2] << endl;
	} while (fp == -2 && (next < dataEnd));
	if (fp == -2)return 1;
	*wp = fp;
	name->clear();
	name->append(buf);
	return 0;
}

void FileTransfer::setData() {
	char tmp[8];
	char tmp2;
	*(long long*)tmp = mFileIfstream.tellg();
	tmp2 = mData.tellp();
	mData.seekp(nowData);
	mData.write(tmp, 8);
	mData.seekg(tmp2);
}
void FileTransfer::endData() {
	char tmp[8];
	char tmp2;
	*(long long*)tmp = -2;
	tmp2 = mData.tellp();
	mData.seekp(nowData);
	mData.write(tmp, 8);
	mData.seekg(tmp2);
}

int FileTransfer::FileStreamOpen()
{

	mFileIfstream.open(mFileName.c_str(), ios::in | ios::binary);

	if (! mFileIfstream.is_open())
	{
		cout << "ERROR: Open fail" << endl;
		
		return -1;
	}
	mFileIfstream.seekg(0, ios::end);
	thisFileSize = mFileIfstream.tellg();
	mFileIfstream.seekg(0, ios::beg);

	// first packet
	mPacket->metaData = -2;
	if (isRe) {
		*(long long*)mPacket->dataBuffer = wp;
		mFileIfstream.seekg(wp);
		isRe = false;
	}
	else {
		*(long long*)mPacket->dataBuffer = 0;
	}
	*(long long*)&mPacket->dataBuffer[8] = thisFileSize;
	strcpy(&mPacket->dataBuffer[16], mFileName.c_str());
	
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


int FileTransfer::isRet(string *ip, string *name) {
	ifstream fp(DATA_FILE_NAME, ios::in | ios::_Nocreate);
	if (fp.is_open()) {
		char tmp[50];
		int leng;
		fp.read(tmp, 15);
		tmp[15] = '\0';
		ip->clear();
		ip->append(tmp);
		fp.read(tmp, 4);
		fp.seekg(10, ios::cur);
		leng = *(int*)tmp - fp.tellg();
		fp.read(tmp, leng);
		tmp[leng] = '\0';
		name->clear();
		name->append(tmp);
		return 1;
	}
	return 0;
}


void FileTransfer::closeData() {
	mData.close();
	remove(DATA_FILE_NAME);
}