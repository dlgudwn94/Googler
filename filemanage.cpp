#include "filemanage.h"

FileManage::FileManage(char *name) {
	SetFileName(name);
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

int FileManage::WriteFile(char *buffer) {
	if (!File)return 2;//파일open안됨
	if (strcmp(buffer, STRING_COMPARE) == 0)return 1; //종료문자열
	File.write(buffer, BUFFERSIZE);
	return 0;
}
