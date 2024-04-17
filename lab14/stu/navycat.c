#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

struct addrinfo hints;
struct addrinfo *result;
struct sockaddr_in * saddr;
char * hostname;
char in_buf[BUF_SIZE];
char out_buf[BUF_SIZE];
int port;
int sock;
int i, s, r;	

pthread_t send_thread, receive_thread;

void cleanup() {	// Handles CTRL-C
	close(sock);
	exit(0);
}

void * sender() {
	// TODO: While there is data that can be read from stdin, read
	//   it and send it to the socket
	//   Use 's' to count bytes to send
	// Exit if there is a write error




}

void * receiver() {
	// TODO: While there is data that can be read from the socket, read
	//   it and send it to stdout
	//   Use 'r' to count bytes read
	// Exit if there is a write error





}

int main(int argc, char * argv[]){

	signal(SIGINT, cleanup);

	if( argc < 3 ){
		fprintf(stderr, "ERROR: require arguments\n");
		exit(1);
	}

	if(sscanf(argv[2], "%d", &port) < 1){
		fprintf(stderr, "ERROR: invalid port\n");
		exit(1);
	}

	hostname = argv[1];
  
	// TODO: Set up address resolution hints



	// TODO: Use getaddrinfo() to resolve hostname.



	// TODO: Properly set IP address and port in saddr


  
 	// TODO: Open the socket (sock)



	// TODO: Connect the socket



	// TODO: Create the sender and receiver threads



	// TODO: Have the main thread wait on the sender and receiver threads



	exit(0);
}