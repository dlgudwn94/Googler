#include <iostream>
#include "fileStream.h"

#define SOCKETNUM 8888
using namespace std;


int main(void) {

	cout << "hi" << endl;
	fileStream ins = fileStream();

	ins.functionA(3);
	return 0;
}