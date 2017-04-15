#include "filemanage.h"

#define DEBUG false

FileManage::FileManage(char* buffer) {
	FileOpenFlag = 1;
	this->mRecvBuffer = buffer;
}

FileManage::~FileManage() {
	if (File) {
		File.close();
	}
}

int FileManage::SetFileName(char *name) {
	this->FileName = name;
	if (FileName.size() > 0) {
		cout << "Recive File Name:" << name <<"<-"<< endl;
		File.open(name, ios::out|ios::binary);
		if (File) {
			FileOpenFlag = 0;//파일 열림
		}
		else {
			cout << "ERRER Recive Wrong File Name :" << name << endl;
		}
	}
	return FileOpenFlag;
}

int FileManage::SetFileNameFromBuf() {
	this->FileName = this->mRecvBuffer;
	if (FileName.size() > 0) {
		File.open(FileName, ios::out|ios::binary);
		if (File) {
			FileOpenFlag = 0;//파일 열림
		}
	}
	return FileOpenFlag;
}

int FileManage::WriteFile() {
	if (FileOpenFlag)return 2;//파일open안됨
	File.write(pk->buff, STRUCT_SIZE);
	return 0;
}

int FileManage::FileEnd() {
	if (FileOpenFlag)return 2;//파일open안됨
	if (pk->meta < 0 || pk->meta > STRUCT_SIZE)return 3;//잘못된 인자
	File.write(pk->buff,pk->meta);
	File.close();
	FileOpenFlag = 1;
	cout << "comlite!" << endl;
	return 0;
}

int FileManage::RecvPacket() {
	pk = (packet*)mRecvBuffer;

	if(DEBUG)
		cout << "meta:" << pk->meta << ",buf:" << pk->buff << "<-\n";

	switch (pk->meta)
	{
	case -2://이름
		return SetFileName(pk->buff);
		break;
	case -1://내용
		return WriteFile();
		break;
	default://0~buffsize 내용끝
		return FileEnd();
		break;
	}
}

int FileManage::IsOpen() {
	return FileOpenFlag;
}