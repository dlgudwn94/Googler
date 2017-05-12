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
	//cout << "comlite!" << endl;
	return 0;
}

int FileManage::FileClose() {
	File.close();
	FileOpenFlag = 1;
	return 0;
}

int FileManage::Complete() {
	FileClose();
	GetMd5();
	return 0;
}

int FileManage::GetMd5() {
	receive_md5 = pk->buff;
	MakeMd5();
	cout << "receive md5:" << receive_md5 << endl;
	cout << "make md5:" << make_md5 << endl;
	if (receive_md5.compare( make_md5) == 0) {

	}
	return 0;
}

int FileManage::MakeMd5() {
	md5wrapper md5;
	make_md5 = md5.getHashFromFile(FileName);
	return 0;
}

int FileManage::GetFolderName() {
	_mkdir(pk->buff);
	return 0;
}

int FileManage::RecvPacket() {
	pk = (packet*)mRecvBuffer;

	if(DEBUG)
		cout << "meta:" << pk->meta << ",buf:" << pk->buff << "<-\n";

	switch (pk->meta)
	{
	case -4://디렉토리명 받음
		return GetFolderName();
		break;
	case -3://마지막 md5값들어옴
		return Complete();
		break;
	case -2://이름
		cout << "전송 시작" << endl;
		return SetFileName(pk->buff);
		break;
	case -1://내용
		return WriteFile();
		break;
	default://0~buffsize 내용끝
		cout << "전송 완료 -> 대기" << endl;
		return FileEnd();
		break;
	}
}

int FileManage::IsOpen() {
	cout << pk->meta;
	return FileOpenFlag;
}