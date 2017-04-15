#include "filemanage.h"

FileManage::FileManage(char* recvBuffer) {
	this->mRecvBuffer = recvBuffer;
	this->isTransferComplete = false;
}

FileManage::~FileManage() {
	mFilefstream.close();
}

int FileManage::FileStreamOpen() {
	//deseriaize
	Deserialization();

	if (mPacket.metaData != 2) {
		cout << "ERROR: Usage Packet" << endl;
		return -2;
	}
	mFileName = mPacket.dataBuffer;
	//mFileName = "test2.jpg";

	mFilefstream.open(mFileName, ios::out | ios::binary);
	if (!mFilefstream.is_open()) {
		cout << "ERROR: Open Fail" << endl;
		return -1;
	}

	return 0;
}

int FileManage::UnpackPacket() {
	//deserialize
	Deserialization();

	int meta = mPacket.metaData;

	if (meta == 1) {
		cout << "받는중" << endl;
		mFilefstream.write(mPacket.dataBuffer, mPacket.dataLength);
		return -1;
	}
	else if (meta == 0) {
		mFilefstream.write(mPacket.dataBuffer, mPacket.dataLength);
		isTransferComplete = true;
		return 0;
	}

	return -2;
}

bool FileManage::isComplete() {
	return isTransferComplete;
}

void FileManage::Deserialization() {
	cout << "dse start : "<< endl;
	char temp[BUFF_SIZE + 1];
	strncpy_s(temp, mRecvBuffer, BUFF_SIZE);
	
	cout << mRecvBuffer << endl;
	mPacket.metaData = temp[0] - 48;

	char length[5];
	length[0] = temp[1];
	length[1] = temp[2];
	length[2] = temp[3];
	length[3] = temp[4];
	length[4] = '\n';
	mPacket.dataLength = atoi(length);

	
	memcpy(mPacket.dataBuffer, &temp[5], DATA_SIZE);

	cout << mPacket.metaData << " " << mPacket.dataLength<< endl;
}

/*
int FileManage::(char *name) {
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
	File.write(pk->buff, STRUCT_SIZE);
	return 0;
}

int FileManage::FileEnd() {
	if (!FileOpenFlag)return 2;//파일open안됨
	if (pk->meta < 0 || pk->meta > STRUCT_SIZE)return 3;//잘못된 인자
	File.write(pk->buff,pk->meta);
	FileOpenFlag = 0;
	return 0;
}

int FileManage::RecvPacket() {
	pk = (packet*)mRecvBuffer;
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
*/