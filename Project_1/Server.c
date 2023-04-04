#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h> /* for atoi() and exit() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */




#define MAXPENDING 5 /* Maximum outstanding connection requests */
#define BUFFER_SIZE 1024


void DieWithError(char *errorMessage); /* Error handling function */
void HandleTCPClient(int clntSocket); /* TCP client handling function */

int main(int argc, char *argv[])
{ 
fflush(stdout);

int serverSocket; /*Socket descriptor for server */
int clientSocket; /* Socket descriptor for client */
struct sockaddr_in ServAddr; /* Local address */
struct sockaddr_in ClntAddr; /* Client address */

unsigned short ServPort; /* Server port */
unsigned int clntLen; /* Length of client address data structure */
if (argc != 2) /* Test for correct number of arguments */
{
fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
exit(1);
}
ServPort = atoi(argv[1]); /* First arg: local port */
/* Create socket for incoming connections */
if ((servSock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
DieWithError("socket() failed"); 

/* Construct local address structure */
memset(&ServAddr, 0, sizeof(ServAddr)); /* Zero out structure */
ServAddr.sin_family = AF_INET; /* Internet address family */
ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
ServAddr.sin_port = htons(ServPort); /* Local port */
/* Bind to the local address */
if (bind (servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr))<0)
DieWithError("bind() failed");
/* Mark the socket so it will listen for incoming connections */
if (listen (servSock, MAXPENDING) < 0)
DieWithError("listen() failed");

for (;;) /* Run forever */
{
/* Set the size of the in-out parameter */
clntLen = sizeof(ClntAddr); /* Wait for a client to connect */
if ((clntSock = accept (servSock, (struct sockaddr *) &ClntAddr, &clntLen)) < 0)
DieWithError("accept() failed");
/* clntSock is connected to a client! */
printf("Handling client %s\n", inet_ntoa(ClntAddr.sin_addr));
HandleTCPClient(clntSock);
}

} 
void DieWithError(char *errorMessage)
{

	printf(errorMessage);

}
void HandleTCPClient(int clntSocket) /* TCP client handling function */
{
	char buf[BUFFER_SIZE];
	int read = recv(clntSocket, buf, BUFFER_SIZE, 0);
      	if (read < 0) DieWithError("Client read failed\n");
	
	int err = send(clntSocket, buf, read, 0);
      	if (err < 0) DieWithError("Client write failed\n");
}
/* NOT REACHED */
