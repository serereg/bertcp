#include <string>
#include <iostream>
#include "Client.h"

int main()
{
	using namespace std;
	using namespace BERTCP;
	//
	try
	{
		Client& client = Client::TheClient();
		//
		string msg = "Hello from client!";
		unsigned char p[4096];
		for (size_t j = 0; j <= msg.size(); ++j)
			p[j] = msg[j];
		client.sendMessage(p, msg.size()+1);
	}
	catch (Exception& e1)
	{
		cout << e1 << endl;
	}
	//
	return 0;
}
