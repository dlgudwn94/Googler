#ifndef _ZIPUNZIP
#define _ZIPUNZIP

#include <windows.h>
#include <iostream>
#include "zlib/zipper.h"
#include "zlib/unzipper.h"
using namespace std;

class zipper{
public:
	int Zipper_Zip(char *srcFileName);
	int Zipper_Unzip(char *srcFileName);
private:
	bool bSrcIsDirectory;
	int Zipper_isDir(char *srcFileName);
};


int zipper::Zipper_Zip(char *srcFileName) {

	bool br;
	Zipper_isDir(srcFileName);
	// 디렉토리인 경우
	if (bSrcIsDirectory) {
		br = CZipper::ZipFolder(srcFileName, FALSE);
	}
	// 파일인 경우
	else {
		br = CZipper::ZipFile(srcFileName);
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

int zipper::Zipper_Unzip(char *srcFileName) {
	bool br;
	Zipper_isDir(srcFileName);
	// 디렉토리인 경우
	if (bSrcIsDirectory) {
		cout << srcFileName << " isn't a file" << endl;
		return 1;
	}
	// 파일인 경우
	else {
		CUnzipper uz;
		br = uz.OpenZip(srcFileName);
		if (br) br = uz.UnzipTo(".");
		if (!br) br = uz.UnzipTo(".",TRUE);
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

int zipper::Zipper_isDir(char *srcFileName) {
	DWORD fileAttr;
	bSrcIsDirectory = ((fileAttr = GetFileAttributes(srcFileName)) & FILE_ATTRIBUTE_DIRECTORY) > 0;
	if (fileAttr == 0xFFFFFFFF) {
		cout << "file not exist or has unknown problems" << endl;
		return 1;
	}
	return 0;
}

#endif // _ZIPUNZIP