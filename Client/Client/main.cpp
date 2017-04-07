#include <iostream>
#include <stdlib.h>
#include "client.h"

using namespace std;

int main()
{
	cout << "Network client" << endl;
	client ins = client();
	ins.print();

	system("pause");
	return 0;
}
