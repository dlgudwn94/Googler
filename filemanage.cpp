#include "filemanage.h"

FileManage::FileManage(char* buffer, int buf_size) {
	FileOpenFlag = 0;
	this->mRecvBuffer = buffer;
	this->mBuf_size = buf_size;
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
	if (strcmp(pk->buff, STRING_COMPARE) == 0) {
		File.close(); //파일을 닫음
		cout << "Complite!"<<endl;
		return 1; //종료문자열
	}
	File.write(pk->buff, BUFFER_SIZE);
	return 0;
}

int FileManage::FileEnd() {
	if (!FileOpenFlag)return 2;//파일open안됨
	if (pk->meta < 0 || pk->meta > BUFFER_SIZE)return 3;//잘못된 인자
	File.write(pk->buff,pk->meta);
	FileOpenFlag = 0;
	return 0;
}

int FileManage::RecvPacket() {
	pk = (packet*)mRecvBuffer;
	switch (pk->meta)
	{
	case -2://이름
		SetFileName(pk->buff);
		break;
	case -1://내용
		WriteFile();
		break;
	default://0~buffsize 내용끝
		FileEnd();
		break;
	}

}

int FileManage::IsOpen() {
	return FileOpenFlag;
}