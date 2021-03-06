// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <cstdlib>
#include <Ws2tcpip.h>

using namespace std;

#pragma warning(disable:4996)

#pragma comment(lib, "ws2_32.lib") //Winsock Library

int main(int argc, char *argv[]) {
	WSADATA wsa;
	SOCKET s;
	sockaddr_in service;
	char *message, server_reply[2000];
	int recv_size;

	//wsadata
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	//connect
	service.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &service.sin_addr);
	//service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(7);


	if (connect(s, (struct sockaddr *)&service, sizeof(service)) < 0)
	{
		puts("connect error");
		return 1;
	}
	else
	{
		printf("connected");
	}
	/*
	char str[100];
	char *check[1];
	char test[10000];
	printf("\nWrite message (max 100 characters): ");
	do {
		cin >> test;
		if (strlen(test) > 100) {
			check[1] = '0';
			memset(test, 0, sizeof(test));
			printf("\nOver 100 characters, write proper message:");
		}
		else
		{
			check[1] = '1';
			for(int i = 0; i<sizeof(str); i++)
			str[i] = test[i];
		}
	} while (check[1] == '0');
	*/
	char str[100];

	printf("\nMessage: ");

	cin >> str;

	//Send data
	message = str;
	if (send(s, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	//Receive data from server
	if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}

	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts(server_reply);
	WSACleanup();

	return 0;
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
