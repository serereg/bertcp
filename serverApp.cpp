#include "Server.h"

int main()
{
	using namespace BERTCP;
	//
    WSADATA wsdata;
    WSAStartup(0x0101,&wsdata);

	Server::TheServer().run();
	//
    WSACleanup();
	return 0;
}
