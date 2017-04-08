#pragma once

#ifndef __FILEMANAGE
#define __FILEMANAGE

#include <iostream>
#include <fstream>
#include <string>

#define STRING_COMPARE "FFFFFFFF"

using namespace std;

class FileManage {
private:
	string FileName;
	fstream File;
	char* mRecvBuffer;
	int mBuf_size;

public:
	FileManage(char *name, char* buffer, int BUFF_SIZE);
	~FileManage();
	int SetFileName(char *name); //파일명이 이미 존재하면 애러 리턴(0:정상, 1:파일존재)
	int WriteFile(); //종료인자를 읽었다면 종료인자 리턴(0:계속, 1:종료, 2:파일open안됨)
};



#endif // !__FILEMANAGE
