#include <iosteam>
#include "Client_File.h"

int main(void) {

	iostream::cout<<"Network client"<< endl;
	Client_File ins = Client_File();
	ins.print();

	return 0;
}