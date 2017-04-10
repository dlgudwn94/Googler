#include "filemanage.h"

FileManage::FileManage(char* buffer, int BUFF_SIZE) {
	FileOpenFlag = 0;
	this->mRecvBuffer = buffer;
	this->mBuf_size = BUFF_SIZE;
}

FileManage::~FileManage() {
	if (File) {
		File.close();
	}
}

int FileManage::SetFileName(char *name) {
	this->FileName = name;
	if (FileName.size() > 0) {
		File.open(name, ios::out);
		if (File) {
			cout << "Recive File:" << name<<endl;
			FileOpenFlag = 1;//파일 열림
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
		File.open(FileName, ios::out);
		if (File) {
			FileOpenFlag = 1;//파일 열림
		}
	}
	return FileOpenFlag;
}

int FileManage::WriteFile() {
	if (!FileOpenFlag)return 2;//파일open안됨
	if (strcmp(mRecvBuffer, STRING_COMPARE) == 0) {
		File.close(); //파일을 닫음
		cout << "Complite!"<<endl;
		return 1; //종료문자열
	}
	File.write(mRecvBuffer, mBuf_size);
	return 0;
}

int FileManage::IsOpen() {
	return FileOpenFlag;
}