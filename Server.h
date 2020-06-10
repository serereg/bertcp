#pragma once

#include "Common.h"
#include "Message.h"

namespace BERTCP
{
	class Server
	{
	public:
		inline static Server& TheServer()
		{
			static Server s;
			return s;
		}	

	public:
		void run()
		{
			// unsigned char* data, size_t len

			int listenfd, new_socket, valread; 
		    struct sockaddr_in address; 
            char opt = 1;
		    int addrlen = sizeof(address); 
		    unsigned char buffer[1024] = {0}; 
		    char *hello = "Hello from server!"; 
		       
		    // Creating socket file descriptor 
		    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
		    { 
		        throw Exception("socket failed"); 
		    } 
		       
            if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR,
		                                                  &opt, sizeof(opt))) 
		    { 
		        throw Exception("setsockopt"); 
		    } 

		    address.sin_family = AF_INET; 
		    address.sin_addr.s_addr = INADDR_ANY; 
		    address.sin_port = htons( PORT ); 
		       
		    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) < 0) 
		    { 
		        throw Exception("bind failed"); 
		    } 
		    if (listen(listenfd, 10) < 0) 
		    { 
		        throw Exception("listen"); 
		    } 
		    while (true)
		    {
		    	cout << "listening..." << endl;
			    new_socket = accept(listenfd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
			    if (new_socket < 0) 
			    { 
			        throw Exception("accept"); 
			    } 
			    //
			    Message M;
			    //
			    bool starting = true;
			    int it = 0;
			    while (true)
			    {
			    	cout << "S:" << it << endl;
			    	it++;
				    valread = read(new_socket, buffer, 1024);
				    if (valread == 0)
				    	break;
				    if (starting)
				    {
				    	M.startReceiving(buffer);
				    	starting = false;
				    	cout << "msg length = " << M.length() << "   ( " << valread << " )" << endl;
				    }
			    	cout << "1" << endl;
				    M.receive(1024, buffer);
			    	cout << "2" << endl;
				    if (M.transferCompleted())
				    	break;
			    	cout << "3" << endl;
				}
			    cout << "!!" << endl;
			    //
			    cout << string((const char*)M.binary()) << endl; 
			    //
			    string s = "Message received @ server!";
			    for (int j = 0; j <= s.size(); ++j)
			    	buffer[j] = s[j];
			    //
			    cout << "...replying..." << endl;
			    Message reply;
				reply.attachBlob(buffer, s.size()+1);
				while (true)
				{
					unsigned char buf[1024];
                    auto bytesSent = reply.send(sizeof(buf), buf);
					cout << "( " << bytesSent << ")" << endl;
                    send(new_socket, (char*)buf, bytesSent, 0);
				    cout << "sending " << bytesSent << " bytes" << endl;
					if (reply.transferCompleted())
						break;
				}
			    // send(new_socket, hello, 18, 0); 
			    // printf("Hello message sent\n"); 
			    close(new_socket);
			}
		}
	};
}
