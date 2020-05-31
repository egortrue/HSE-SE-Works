#ifndef SERVER_H
#define SERVER_H

#pragma comment(lib, "Ws2_32.lib")

#define HAVE_STRUCT_TIMESPEC
#define MAX_DATA_SIZE 1024
#define MAX_CLIENTS_ONLINE 50

#include <pthread.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>

enum server_status {stopped, started};
enum client_status {offline, online};

//===========================================================

typedef struct st_client
{
	SOCKET socket;
	SOCKADDR_IN address;
	pthread_t thread;

	char* name;
	unsigned int id;
	unsigned char status : 1;
}CLIENT;

CLIENT* ClientCreate  (SOCKET sock, SOCKADDR_IN sock_addr);
  void* ClientDestroy (CLIENT* client);
  void* ClientRun     (void* client_param);

//===========================================================

typedef struct st_server
{
	SOCKET socket;
	SOCKADDR_IN address;
	pthread_t thread;
	time_t time_start;
	CLIENT** clients;

	unsigned int active_connections;
	unsigned int clients_online;
	unsigned char status : 1;

}SERVER;

SERVER* ServerCreate  ();
  void* ServerDestroy (SERVER* server);
  void* ServerRun     (void* server_param); // Start main thread
  void  ServerStop    (SERVER* server);     // Close main thread

//===========================================================
// Other functions

FILE* FileOpen (const char* name, const char* mode);
void  LogWrite (char* string);


#endif