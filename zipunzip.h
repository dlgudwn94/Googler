#ifndef _ZIPUNZIP
#define _ZIPUNZIP

#include <windows.h>
#include <iostream>
#include "zlib/zipper.h"
#include "zlib/unzipper.h"
#include <string>

using namespace std;

class zipper{
public:
	int Zipper_Zip();
	int Zipper_Unzip();
	void Set_Name(string srcFileName);
private:
	bool bSrcIsDirectory;
	int Zipper_isDir();
	string srcFileName;
};

void zipper::Set_Name(string FileName) {
	srcFileName = FileName;
}

int zipper::Zipper_Zip() {

	bool br;
	Zipper_isDir();
	// 디렉토리인 경우
	if (bSrcIsDirectory) {
		br = CZipper::ZipFolder(srcFileName.c_str(), FALSE);
	}
	// 파일인 경우
	else {
		br = CZipper::ZipFile(srcFileName.c_str());
	}
	if (br) {
		cout << "compression completed." << endl;
	}
	else {
		cout << "error occured." << endl;
		return 1;
	}
	return 0;
}

int zipper::Zipper_Unzip() {
	bool br;
	char getdir[MAX_PATH];
	Zipper_isDir();
	GetCurrentDirectory(MAX_PATH, getdir);
	string dir(getdir);
	dir.append("\\");
	// 디렉토리인 경우
	if (bSrcIsDirectory) {
		cout << srcFileName << " isn't a file" << endl;
		return 1;
	}
	// 파일인 경우
	else {
		CUnzipper uz;
		br = uz.OpenZip(srcFileName.c_str());
		if (br) br = uz.UnzipTo(dir.c_str());
		if (!br) br = uz.UnzipTo(dir.c_str(), TRUE);
		if (br) {
			cout << "decompression completed." << endl;
		}
		else {
			cout << "error occured." << endl;
			return 1;
		}
	}
	return 0;
}

int zipper::Zipper_isDir() {
	DWORD fileAttr;
	bSrcIsDirectory = ((fileAttr = GetFileAttributes(srcFileName.c_str())) & FILE_ATTRIBUTE_DIRECTORY) > 0;
	if (fileAttr == 0xFFFFFFFF) {
		cout << "file not exist or has unknown problems" << endl;
		return 1;
	}
	return 0;
}

#endif // _ZIPUNZIP