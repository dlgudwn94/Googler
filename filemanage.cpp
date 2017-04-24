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
			FileOpenFlag = 0;//���� ����
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
			FileOpenFlag = 0;//���� ����
		}
	}
	return FileOpenFlag;
}

int FileManage::WriteFile() {
	if (FileOpenFlag)return 2;//����open�ȵ�
	File.write(pk->buff, STRUCT_SIZE);
	return 0;
}

int FileManage::FileEnd() {
	if (FileOpenFlag)return 2;//����open�ȵ�
	if (pk->meta < 0 || pk->meta > STRUCT_SIZE)return 3;//�߸��� ����
	File.write(pk->buff,pk->meta);
	//cout << "comlite!" << endl;
	return 0;
}

int FileManage::FileClose() {
	File.close();
	FileOpenFlag = 1;
	return 0;
}

int FileManage::GetMd5() {
	FileClose();
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

int FileManage::RecvPacket() {
	pk = (packet*)mRecvBuffer;

	if(DEBUG)
		cout << "meta:" << pk->meta << ",buf:" << pk->buff << "<-\n";

	switch (pk->meta)
	{
	case -3://md5��
		return GetMd5();
		break;
	case -2://�̸�
		return SetFileName(pk->buff);
		break;
	case -1://����
		return WriteFile();
		break;
	default://0~buffsize ���볡
		return FileEnd();
		break;
	}
}

int FileManage::IsOpen() {
	cout << pk->meta;
	return FileOpenFlag;
}