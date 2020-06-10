#pragma once

#define OS_WINDOWS

#ifdef OS_WINDOWS
    #define _WIN32_WINNT 0x0600
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <windows.h>
    #include <ws2tcpip.h>
#else
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

#include <iostream>
#include "Exception.h"

#define PORT 27015    //8888
