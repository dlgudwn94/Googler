#include "ServerManager.h"

int main(void) {
	ServerManager* InsSM;
	char* fileName;

	cout << "저장될 파일 이름 :";
	cin >> fileName;
	InsSM = new ServerManager(fileName);
	InsSM->FileRecvStart();

	return 0;

}