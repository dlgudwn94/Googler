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
	int mBuf_size;
	char* mRecvBuffer;
	string FileName;
	fstream File;
	char FileOpenFlag;

public:
	FileManage(char* buffer, int BUFF_SIZE);
	~FileManage();
	int SetFileName(char *name); //파일명이 이미 존재하면 애러 리턴(0:정상, 1:파일존재)
	int SetFileNameFromBuf(); //버퍼에서 직접 가져옴
	int WriteFile(); //종료인자를 읽었다면 종료인자 리턴(0:계속, 1:종료, 2:파일open안됨)
	int IsOpen(); //파일이 열려있는지 확인(1:열림,0:닫힘)
};



#endif // !__FILEMANAGE
