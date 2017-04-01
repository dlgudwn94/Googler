#include "server.h"

int main(void) {
	Server sevIns(8888);

	sevIns.ConnectUDP();

}