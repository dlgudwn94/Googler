#ifndef SEARCH_DIR
#define SEARCH_DIR

#include <io.h>
#include <conio.h>
#include <string>

using namespace std;

class SearchDirectory {
public:
	void MakeDirList(std::string src);
	void SetDirList(std::string dirlist);
	std::string DirList();
	std::string GetDir();
	int CheckIfDir(std::string src);
private:
	void ListMaking(std::string srcRoot, std::string dir);
	std::string root;
	std::string DirectoryList;
};

void SearchDirectory::MakeDirList(std::string src) {
	int flg = CheckIfDir(src);
	root = src.substr(src.find_last_of("\\") + 1, src.length());
	if (flg == 0) {//����
		DirectoryList = "?D";
		DirectoryList.append(root);
		ListMaking(src.substr(0, src.find_last_of("\\") + 1), root);
		DirectoryList.append("??");
	}
	else if (flg == 1) {//�������� ����
		DirectoryList = "??";
	}
	else {//����
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
	if (handle == -1)return 1;//���Ͼ���
	tmp = fd.attrib;
	_findclose(handle);
	if (tmp == 16)return 0;//�����̴�
	return 2;//������ �ƴϴ�
}

void SearchDirectory::ListMaking(std::string srcRoot, std::string dir)
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst((srcRoot + dir + "\\*.*").c_str(), &fd);  //���� ���� �� ��� ������ ã�´�.

	if (handle == -1)
	{
		//There were no files.
		return;
	}

	while (result != -1)
	{
		if (fd.attrib == 16) {//���丮
			if (std::strcmp(".", fd.name) != 0 && std::strcmp("..", fd.name) != 0) {
				DirectoryList.append("?D");
				DirectoryList.append(dir);
				DirectoryList.append("\\");
				DirectoryList.append(fd.name);
				ListMaking(srcRoot, dir + "\\" + fd.name);//��������� �߰�
			}
		}
		else {//����
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