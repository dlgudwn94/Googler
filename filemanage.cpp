#include "filemanage.h"

FileManage::FileManage(char *name, char* buffer, int BUFF_SIZE) {
	SetFileName(name);
	this->mRecvBuffer = buffer;
	this->mBuf_size = BUFF_SIZE;
}

FileManage::~FileManage() {
	File.close();
}

int FileManage::SetFileName(char *name) {
	this->FileName = name;
	if (FileName.size() > 0) {
		File.open(name, ios::out);
	}
}

int FileManage::WriteFile() {
	if (!File)return 2;//파일open안됨
	if (strcmp(mRecvBuffer, STRING_COMPARE) == 0)return 1; //종료문자열
	File.write(mRecvBuffer, mBuf_size);
	return 0;
}
