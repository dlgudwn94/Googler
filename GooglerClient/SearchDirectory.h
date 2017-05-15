#ifndef SEARCH_DIR
#define SEARCH_DIR

#include <io.h>
#include <conio.h>
#include <string>
#include <fstream>
#define DATA_FILE_NAME "RD.dat"
using namespace std;

class SearchDirectory {
public:
	void MakeDirList(std::string src);
	void MakeListFile();
	void SetDirList(std::string dirlist);
	std::string DirList();
	std::string GetDir();
	int CheckIfDir(std::string src);
private:
	void ListMaking(std::string srcRoot, std::string dir);
	std::string root;
	std::string DirectoryList;
};

void SearchDirectory::MakeListFile() {
	ofstream file(DATA_FILE_NAME, ios::out | ios::binary | ios::trunc);
	string name;
	string tmpDirectoryList = DirectoryList;
	int p, end;
	char zero[12] = { 0, };
	int index;
	char next[4];
	while (true) {
		index = file.tellp();
		p = tmpDirectoryList.find('?');
		end = tmpDirectoryList.find('?', p + 1);
		name = tmpDirectoryList.substr(p, end);
		if (end == p + 1)break;
		file.write(zero, 12);
		file.write(name.c_str(), name.length());
		*(int*)next = file.tellp();
		file.seekp(index);
		file.write(next, 4);
		file.seekp(*(int*)next);
		tmpDirectoryList = tmpDirectoryList.substr(end, tmpDirectoryList.length());
	}
	file.close();
}

void SearchDirectory::MakeDirList(std::string src) {
	int flg = CheckIfDir(src);
	root = src.substr(src.find_last_of("\\") + 1, src.length());
	if (flg == 0) {//폴더
		DirectoryList = "?D";
		DirectoryList.append(root);
		ListMaking(src.substr(0, src.find_last_of("\\") + 1), root);
		DirectoryList.append("??");
	}
	else if (flg == 1) {//존재하지 않음
		DirectoryList = "??";
	}
	else {//파일
		DirectoryList = "?E";
		DirectoryList.append(root);
		DirectoryList.append("??");
	}
}

void SearchDirectory::SetDirList(std::string dirlist) {
	DirectoryList = dirlist;
}
std::string SearchDirectory::DirList() {
	return DirectoryList;
}

std::string SearchDirectory::GetDir() {
	std::string name;
	int p = DirectoryList.find('?');
	int end = DirectoryList.find('?', p + 1);
	name = DirectoryList.substr(p, end);
	if (end == p + 1)return name;
	DirectoryList = DirectoryList.substr(end, DirectoryList.length());
	return name;
}

int SearchDirectory::CheckIfDir(std::string src) {
	_finddata_t fd;
	long handle;
	int tmp;
	handle = _findfirst(src.c_str(), &fd);
	if (handle == -1)return 1;//파일없음
	tmp = fd.attrib;
	_findclose(handle);
	if (tmp == 16)return 0;//폴더이다
	return 2;//폴더가 아니다
}

void SearchDirectory::ListMaking(std::string srcRoot, std::string dir)
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst((srcRoot + dir + "\\*.*").c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		//There were no files.
		return;
	}

	while (result != -1)
	{
		if (fd.attrib == 16) {//디렉토리
			if (std::strcmp(".", fd.name) != 0 && std::strcmp("..", fd.name) != 0) {
				DirectoryList.append("?D");
				DirectoryList.append(dir);
				DirectoryList.append("\\");
				DirectoryList.append(fd.name);
				ListMaking(srcRoot, dir + "\\" + fd.name);//재귀적으로 추가
			}
		}
		else {//파일
			DirectoryList.append("?E");
			DirectoryList.append(dir);
			DirectoryList.append("\\");
			DirectoryList.append(fd.name);
		}
		//printf("File: %s,%d,%d\n", fd.name, fd.attrib, fd.size);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return;
}

#endif // !SEARCH_DIR