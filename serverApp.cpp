#include "Server.h"

int main()
{
	using namespace BERTCP;
	//
    #ifdef OS_WINDOWS
        WSADATA wsdata;
        WSAStartup(0x0101,&wsdata);
    #endif
	Server::TheServer().run();
	//
    #ifdef OS_WINDOWS
        WSACleanup();
    #endif
    return 0;
}
