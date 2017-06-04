/************************************************************************************
* encryptedmessaging.cpp 
* Authors: Matt Nutsch, Tony Quach
* Date: 6-4-2017
* Description: This is a PC based C++ client for exchanging encrypted messages with
* a web server.
* UNDER DEVELOPMENT!
************************************************************************************/

#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS //we are using deprecated functions in Winsock

#include <iostream>
#include <string>

#include <winsock2.h> //used to get URL content
//#include <windows.h>
#include <ws2tcpip.h> //used to get URL content
#pragma comment(lib,"ws2_32.lib")

using namespace std;

//sign in function
int signInUser(string * argUsername, string * argPassword)
{
	int isSuccessful = 1; //dev note: change from 1 to 0
	string username;
	string password;

	//get user name
	cout << "Enter your username: ";
	cin >> username;
	*argUsername = username;
	
	//get user password
	cout << endl;
	cout << "Enter your password: ";
	cin >> password;
	*argPassword = password;

	cout << endl;

	//get the URL content
	/*****************************************************************************************************************/
	//source: http://www.cplusplus.com/forum/windows/109180/
	WSADATA wsaData;

	int i = 0;

	char *host_name;

	host_name = "httpbin.org"; //DEV NOTE: change this URL to API root, change port, and add POST variables for testing below

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		return 1;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname(host_name);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80); //HTTP
	//SockAddr.sin_port = htons(443); //HTTPS
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	cout << "Connecting...\n";
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		return 1;
	}
	cout << "Connected.\n";

	// dev note change this to the proper URL and to a POST string with the parameters included
	 
	string sendbuf = "GET / HTTP/1.1\r\nHost: "; 
	sendbuf.append(host_name);
	sendbuf.append("\r\nConnection: close\r\n\r\n");

	/*
	string sendbuf = "POST /post/ recv.php HTTP / 1.1\r\n";
	sendbuf.append("Host: ");
	sendbuf.append(host_name);
	sendbuf.append("\r\n");
	sendbuf.append("User-Agent: Mozilla Firefox/4.0\r\n");
	sendbuf.append("Content-Length: %d\r\n");
	sendbuf.append("Content-Type: application/x-www-form-urlencoded\r\n");
	sendbuf.append("Accept-Charset: utf-8\r\n\r\n");
	*/

	send(Socket, sendbuf.c_str(), sendbuf.length(), 0);
	char buffer[10000];
	string buff;
	int nDataLength = 1;
	while (nDataLength != 0)
	{
		buffer[0] = 0;
		nDataLength = recv(Socket, buffer, 10000, 0);
		buff.append(buffer, nDataLength);
		//cout << buffer;
	}

	closesocket(Socket);
	WSACleanup();

	//cout << buff; //DEV NOTE: uncomment this to view the raw output from the web server

	//DEV NOTE: add code here to parse the variable "buff" for the API result
	//depending on the reply from the server, set isSuccessful to 0 for a failure.

	//system("pause");
	/*****************************************************************************************************************/

	return isSuccessful;
}

//get a list of messages to read
//messageSubjects = pointer to array of strings representing the subject of the message
//messageIds = pointer to array of ints representing the id number of the message on the server
void getMessageList(string username, string password, string * messageSubjects[], int * messageIds[])
{
	//contact the message list API
	//DEV NOTE add code to contact API
	//send username as POST
	//send password as POST
	//read messageNames and MessageIds as JSON

	//get the URL content
	/*****************************************************************************************************************/
	//source: http://www.cplusplus.com/forum/windows/109180/
	WSADATA wsaData;

	int i = 0;

	char *host_name;

	host_name = "httpbin.org"; //DEV NOTE: change this URL to API root, change port, and add POST variables for testing below

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		//return 1; //DEV NOTE: change this line
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname(host_name);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80); //HTTP
								   //SockAddr.sin_port = htons(443); //HTTPS
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	cout << "Connecting...\n";
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		//return 1; //DEV NOTE: change this line
	}
	cout << "Connected.\n";

	// dev note change this to the proper URL and to a POST string with the parameters included

	string sendbuf = "GET / HTTP/1.1\r\nHost: ";
	sendbuf.append(host_name);
	sendbuf.append("\r\nConnection: close\r\n\r\n");

	/*
	string sendbuf = "POST /post/ recv.php HTTP / 1.1\r\n";
	sendbuf.append("Host: ");
	sendbuf.append(host_name);
	sendbuf.append("\r\n");
	sendbuf.append("User-Agent: Mozilla Firefox/4.0\r\n");
	sendbuf.append("Content-Length: %d\r\n");
	sendbuf.append("Content-Type: application/x-www-form-urlencoded\r\n");
	sendbuf.append("Accept-Charset: utf-8\r\n\r\n");
	*/

	send(Socket, sendbuf.c_str(), sendbuf.length(), 0);
	char buffer[10000];
	string buff;
	int nDataLength = 1;
	while (nDataLength != 0)
	{
		buffer[0] = 0;
		nDataLength = recv(Socket, buffer, 10000, 0);
		buff.append(buffer, nDataLength);
		//cout << buffer;
	}

	closesocket(Socket);
	WSACleanup();

	//cout << buff; //DEV NOTE: uncomment this to view the raw output from the web server

	/*****************************************************************************************************************/
	
	//DEV NOTE: parse JSON 
	//set messageSubjects = array of strings
	//set messageIds = array of ints

}

//decrypt message function
string decryptMessage(string argMessage)
{
	string decryptedMessage;

	//dev note: add code to decrypy argMessage into decryptedMessage
	//dev note: this function is identical to the encrypt message function since the ROT13 algorithm merely shifts all
	//ASCII values 13 spaces. I wanted to make these separate functions so that when we write main, we don't get confused on which 
	//operation is being performed. 
	char decryptedOutput[1000];
	for (int i = 0; (unsigned int) i < argMessage.size(); i++)
	{
		char c = argMessage[i];
		if (c >= 'a' && c <= 'm') 
		{
			c += 13;
			decryptedOutput[i] = c;
		}
		else if (c >= 'n' && c <= 'z') {
			c -= 13;
			decryptedOutput[i] = c;
		}
		else if (c >= 'A' && c <= 'M') {
			c += 13;
			decryptedOutput[i] = c;
		}
		else if (c >= 'N' && c <= 'Z') {
			c -= 13;
			decryptedOutput[i] = c;
		}
		else {
			decryptedOutput[i] = c;
		}
	}
	return decryptedMessage;
}

//read a specific message from the server
//messageId = the id number of the message in the server database
string getMessage(string username, string password, int messageId)
{
	string message = "";

	//contact the read message API
	//DEV NOTE add code to contact API
	//send username as POST
	//send password as POST
	//send messageId as POST
	//read string from the web server

	//get the URL content
	/*****************************************************************************************************************/
	//source: http://www.cplusplus.com/forum/windows/109180/
	WSADATA wsaData;

	int i = 0;

	char *host_name;

	host_name = "httpbin.org"; //DEV NOTE: change this URL to API root, change port, and add POST variables for testing below

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		//return 1; //DEV NOTE: change this line
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname(host_name);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80); //HTTP
								   //SockAddr.sin_port = htons(443); //HTTPS
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	cout << "Connecting...\n";
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		//return 1; //DEV NOTE: change this line
	}
	cout << "Connected.\n";

	// dev note change this to the proper URL and to a POST string with the parameters included

	string sendbuf = "GET / HTTP/1.1\r\nHost: ";
	sendbuf.append(host_name);
	sendbuf.append("\r\nConnection: close\r\n\r\n");

	/*
	string sendbuf = "POST /post/ recv.php HTTP / 1.1\r\n";
	sendbuf.append("Host: ");
	sendbuf.append(host_name);
	sendbuf.append("\r\n");
	sendbuf.append("User-Agent: Mozilla Firefox/4.0\r\n");
	sendbuf.append("Content-Length: %d\r\n");
	sendbuf.append("Content-Type: application/x-www-form-urlencoded\r\n");
	sendbuf.append("Accept-Charset: utf-8\r\n\r\n");
	*/

	send(Socket, sendbuf.c_str(), sendbuf.length(), 0);
	char buffer[10000];
	string buff;
	int nDataLength = 1;
	while (nDataLength != 0)
	{
		buffer[0] = 0;
		nDataLength = recv(Socket, buffer, 10000, 0);
		buff.append(buffer, nDataLength);
		//cout << buffer;
	}

	closesocket(Socket);
	WSACleanup();

	//cout << buff; //DEV NOTE: uncomment this to view the raw output from the web server

	/*****************************************************************************************************************/

	//DEV NOTE: decrypt the message
	//set message to the decrypted message

	return message;
}

//encrypt function
string encryptString(string argInput)
{

	//dev note add code to encrypt input
	//set encryptedInput to an encrypted version of the argInput

	//dev note: building strings in C++ is confusing, so this builds an array of chars as the output encrypted string
	//probably need to change this a little
	char encryptedInput[1000];
	for (int i = 0; (unsigned int) i < argInput.size(); i++)
	{
		char c = argInput[i];
		if (c >= 'a' && c <= 'm') {
			c += 13;
			encryptedInput[i] = c;
		}
		else if (c >= 'n' && c <= 'z') {
			c -= 13;
			encryptedInput[i] = c;
		}
		else if (c >= 'A' && c <= 'M') {
			c += 13;
			encryptedInput[i] = c;
		}
		else if (c >= 'N' && c <= 'Z') {
			c -= 13;
			encryptedInput[i] = c;
		}
		else {
			encryptedInput[i] = c;
		}
	}
	return encryptedInput;
}

//write a message to a recipent
void writeMessage(string * argRecipient, string * argSubject, string * argMessageBody)
{
	string recipient;
	string subject;
	string messageBody;

	//read recipient
	cout << "Enter the recipient's email address: " << endl;
	getline (cin, recipient);
	cout << endl;

	*argRecipient = recipient;

	//read subject line
	cout << "Enter the subject line: " << endl;
	getline(cin, subject);
	cout << endl;

	*argSubject = subject;

	//read message body
	cout << "Enter the message body: " << endl;
	getline(cin, messageBody);
	cout << endl;

	*argMessageBody = messageBody;

	//encrypt the subject
	subject = encryptString(subject);

	//encrypt the message
	messageBody = encryptString(messageBody);

}

//create key pair function
int createKeyPair(string username, string password)
{
	int isSuccessful = 1;

	//dev note: add code to create a key pair on the PC
	//if this fails, set isSuccessful = 0;

	//dev note: add code to send the public key to the web server api
	//if this fails, set isSuccessful = 0;

	return isSuccessful;
}

//sending the encrypted message to server
int sendMessageToServer(string username, string password, string message, string subject, string recipient)
{
	int isSendSuccessful = 0;
	//encrypt the message
	//dev note call encrypt message function

	//contact the read message API
	//DEV NOTE add code to contact API
	//send username as POST
	//send password as POST
	//send message as POST
	//send subject as POST
	//send recipient as POST
	//set isSendSuccessful = 1 if successful

	/*****************************************************************************************************************/
	//source: http://www.cplusplus.com/forum/windows/109180/
	WSADATA wsaData;

	int i = 0;

	char *host_name;

	host_name = "httpbin.org"; //DEV NOTE: change this URL to API root, change port, and add POST variables for testing below

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		return 1;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname(host_name);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80); //HTTP
								   //SockAddr.sin_port = htons(443); //HTTPS
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	cout << "Connecting...\n";
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		cout << "Could not connect";
		system("pause");
		return 1;
	}
	cout << "Connected.\n";

	// dev note change this to the proper URL and to a POST string with the parameters included

	string sendbuf = "GET / HTTP/1.1\r\nHost: ";
	sendbuf.append(host_name);
	sendbuf.append("\r\nConnection: close\r\n\r\n");

	/*
	string sendbuf = "POST /post/ recv.php HTTP / 1.1\r\n";
	sendbuf.append("Host: ");
	sendbuf.append(host_name);
	sendbuf.append("\r\n");
	sendbuf.append("User-Agent: Mozilla Firefox/4.0\r\n");
	sendbuf.append("Content-Length: %d\r\n");
	sendbuf.append("Content-Type: application/x-www-form-urlencoded\r\n");
	sendbuf.append("Accept-Charset: utf-8\r\n\r\n");
	*/

	send(Socket, sendbuf.c_str(), sendbuf.length(), 0);
	char buffer[10000];
	string buff;
	int nDataLength = 1;
	while (nDataLength != 0)
	{
		buffer[0] = 0;
		nDataLength = recv(Socket, buffer, 10000, 0);
		buff.append(buffer, nDataLength);
		//cout << buffer;
	}

	closesocket(Socket);
	WSACleanup();

	//cout << buff; //DEV NOTE: uncomment this to view the raw output from the web server

	//DEV NOTE: add code here to parse the variable "buff" for the API result
	//depending on the reply from the server, set isSendSuccessful to 0 for a failure.

	//system("pause");
	/*****************************************************************************************************************/

	return isSendSuccessful;
}

//print menu
void printMenu()
{
	cout << "1. Get message list." << endl;
	cout << "2. Read a message." << endl;
	cout << "3. Write a message." << endl;
	cout << "4. Create a key pair." << endl;
	cout << "5. Quit program." << endl;
}

int main()
{
	int isSignedIn = 0;
	char userinput;
	string username;
	string password;
	string messageSubjects[100]; //dev note: change to dynamic array
	int messageIds[100]; //dev note: change to dynamic array
	string message; //temporarily stores the message string
	int messageId; //temporarily stores the message id from user input\

	string recipient;
	string subject;
	string messageBody;

	isSignedIn = signInUser(&username, &password);

	cout << "Welcome " << username << "." << endl << endl;
	//cout << "your password is " << password << endl;

	bool continueLoop = 1;
	while (continueLoop == 1)
	{
		printMenu();
		cin >> userinput;

		switch (userinput) 
		{
			case '1': cout << "You selected get message list."; 
				//get list
				//getMessageList(username, password, &messageSubjects, &messageIds);

				//display list
				//dev note: call function here

				break;
			case '2': cout << "You selected read a message.";
				cout << endl << "type in the message ID: ";
				cin >> messageId;

				//get message
				message = getMessage(username, password, messageId);
				
				//display message
				cout << "Your message is: " << message;

				break;
			case '3': cout << "You selected write a message."; 
				//read the inputs from the user and encrypt
				writeMessage(&recipient, &subject, &messageBody);
				
				//send the message to the server
				sendMessageToServer(username, password, messageBody, subject, recipient);

				break;
			case '4': cout << "You selected create a key pair."; 
				//create the files
				createKeyPair(username, password);

				break;
			case '5': cout << "You selected quit the program."; 
				return 0;
				break;
		}
		cout << endl;
		
	}
    return 0;
}

