#include "filemanage.h"
#define DEBUG false

FileManage::FileManage(char* buffer) {
	FileOpenFlag = 1;
	ignore = 0;
	this->mRecvBuffer = buffer;
}

FileManage::~FileManage() {
	if (File) {
		File.close();
	}
}

int FileManage::SetFileName(char *name,long long wp) {
	if (File)File.close();
	this->FileName = name;
	if (FileName.size() > 0) {
		cout << "Recive File Name:" << name <<"<-"<< endl;
		File.open(name,ios::in|ios::out|ios::binary);
		if(File.is_open()==false)File.open(name, ios::out | ios::binary);
		if (File) {
			FileOpenFlag = 0;//���� ����
			cout << "again:" << wp << endl;
			File.seekp(wp);
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

	string tmpstr;
	if(DEBUG)
		cout << "meta:" << pk->meta << ",buf:" << pk->buff << "<-\n";

	switch (pk->meta)
	{
	case -4://���丮�� ����
		thisFileSize = 0;
		return GetFolderName();
		break;
	case -3://������ md5������
		if (ignore) {
			ignore = 0;
			return 0;
		}
		return Complete();
		break;
	case -2://�̸�
		tmpstr.clear();
		tmpstr.append(&pk->buff[16]);
		this->mLogIns = new Log(&pk->buff[16]);
		if (efilter.checkName(tmpstr)) {
			cout << "�ޱⰡ ���ѵ� Ȯ����: " << tmpstr << endl;
			this->FileName = &pk->buff[16];
			ignore = 1;
		}
		cout << "���� ����" << endl;
		thisFileSize=*(long long*)&pk->buff[8];
		if (ignore)return 0;
		return SetFileName(&pk->buff[16],*(long long*)pk->buff);
		break;
	case -1://����
		if (ignore)return 0;
		return WriteFile();
		break;
	default://0~buffsize ���볡
		if (ignore)return 0;
		cout << "���� �Ϸ� -> ���" << endl;
		mLogIns->writeLog();
		return FileEnd();
		break;
	}
}

int FileManage::IsOpen() {
	cout << pk->meta;
	return FileOpenFlag;
}

int FileManage::FIleSize() {
	return thisFileSize;
}

