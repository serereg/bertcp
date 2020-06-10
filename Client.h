#pragma once

#include "Common.h"
#include "Message.h"

#include "string.h"

namespace BERTCP
{
	class Client
	{
	public:
		inline static Client& TheClient()
		{
			static Client s;
			return s;
		}	

	public:
		void sendMessage(unsigned char* data, size_t len)
		{
            #ifdef OS_WINDOWS
                WSADATA wsaData;
                int iResult;

                // Initialize Winsock
                iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
                if (iResult != 0) {
                    throw Exception("WSAStartup failed with error");
                }
            #endif
			// open
			int sock = 0, valread; 
		    struct sockaddr_in serv_addr; 
		    char *hello = "Hello from client"; 
		    unsigned char buffer[1024] = {0}; 
		    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		    { 
		        throw Exception("Socket creation error"); 
		    } 
		   
		    serv_addr.sin_family = AF_INET; 
		    serv_addr.sin_port = htons(PORT); 

		    // Convert IPv4 and IPv6 addresses from text to binary form 
            if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
            {
                throw Exception("Invalid address/ Address not supported");
            }
		   
		    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
		    { 
		        throw Exception("Connection failed"); 
		    } 
		    // send(sock , hello , strlen(hello) , 0 ); 
		    // printf("Hello message sent\n"); 
			Message msg;
			cout << "!" << endl;
			msg.attachBlob(data, len);
			while (true)
			{
				unsigned char buf[1024];
				cout << "." << endl;
				auto bytesSent = msg.send(1024, buf);
				cout << "1 sending " << bytesSent << "..." << endl;
                            send(sock, (char *)buf, bytesSent, 0 );
				cout << "2" << endl;
				if (msg.transferCompleted())
					break;
				cout << "3" << endl;
			}
			cout << "!!" << endl;
			//
			Message reply;
		    valread = read(sock, buffer, 1024); 
			cout << "( " << valread << " )" << endl;
			reply.startReceiving(buffer);
			reply.receive(1024, buffer);
		    cout << string((const char*)reply.binary()) << endl; 
			
			close(sock);

            #ifdef OS_WINDOWS
                WSACleanup();
            #endif
        }
	};
}
