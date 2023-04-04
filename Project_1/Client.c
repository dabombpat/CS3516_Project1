#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() and exit() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#define RCVBUFSIZE 32 /* Size of receive buffer */


void DieWithError(char *errorMessage); /* Error handling function */ 

int main(int argc, char *argv[])
{
fflush(stdout);


int sock; /* Socket descriptor */
struct sockaddr_in ServAddr; /* Server address */
unsigned short ServPort; /* Server port */
char *servIP; /* Server IP address (dotted quad) */
char* get = "GET / HTTP/1.1\r\n"; /* String to send to http server */
char* host = "Host: ";
char* hostname;
char Buffer[RCVBUFSIZE]; /* Buffer for echo string */
unsigned int HTTPLength; /* Length of string to echo */
int bytesRcvd, totalBytesRcvd; /* Bytes read in single recv()
and total bytes read */

if ((argc < 3) || (argc > 4)) /* Test for correct number of arguments */
{
        fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",
        argv[0]);
        exit(1);
} 

if (argc == 4){
        optionstring = argv[1]; /* First arg: options string */
        hostname = argv[2]; /* Second arg: server IP address (dotted quad) */
        ServPort = atoi(argv[3]); /* Use given port, if any */
}
else{
        hostname = argv[1];
        ServPort = argv[2];
}

char *httpGet = malloc(strlen(get)+strlen(hostname)+strlen(connectionAlive)+10);
strcpy(httpGet,get);
strcat(httpGet,host);
strcat(httpGet,hostname);
strcat(httpGet,connectionAlive);
strcat(httpGet,"\r\n");

printf("%s:%s\n",hostname,ServPort);


if ((sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
DieWithError("socket() failed");

/* Construct the server address structure */
memset(&ServAddr, 0, sizeof(ServAddr)); /* Zero out structure */
ServAddr.sin_family = AF_INET; /* Internet address family */
ServAddr.sin_addr.s_addr = inet_addr(servIP); /* Server IP address */
ServAddr.sin_port = htons(ServPort); /* Server port */


/* Establish the connection to the server */
if (connect (sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
DieWithError("connect() failed");





/* Send the string to the server */
unsigned int sent = send (sock, httpGet, HTTPLength, 0)
printf("Sent: %s\n", httpGet);


/* Receive the same string back from the server */
totalBytesRcvd = 0;
printf("Received: "); /* Setup to print the echoed string */ 

while (bytesRcvd <= RCVBUFSIZE-1 && strstr(Buffer,"</html>")==NULL)
{
/* Receive up to the buffer size (minus 1 to leave space for
 * a null terminator) bytes from the sender */
if ((bytesRcvd = recv(sock, Buffer, RCVBUFSIZE - 1, 0)) <= 0)
DieWithError("recv() failed or connection closed prematurely");

totalBytesRcvd += bytesRcvd; /* Keep tally of total bytes */
Buffer[bytesRcvd] = '\0'; /* Terminate the string! */
printf("%s", Buffer); /* Print the echo buffer */
}
printf("\n"); 
close (sock);
if(optionstring){
printf("RTT: %f\n",((float)(stop.tv_usec-start.tv_usec) + (float)((stop.tv_sec-start.tv_sec)*1000000))/1000);
}
exit(0);
}

void DieWithError(char *errorMessage)
{
        printf(errorMessage);
        printf("\n");
} 
