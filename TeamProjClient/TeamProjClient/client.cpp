#include <iostream>
#include <stdlib.h>
#include "Client_File.h"

using namespace std;

int main(void)
{
	cout<<"Network client"<< endl;
	Client_File ins = Client_File();
	ins.print();

	system("pause");
	return 0;
}