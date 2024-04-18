#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

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
  while( (r = read(0, in_buf, BUF_SIZE)) > 0 ){
    if( write(sock, in_buf, r) < 0 ){
      perror("sender");
      exit(1);
    }
  }  
}

void * receiver() {
  // TODO: While there is data that can be read from the socket, read
  //   it and send it to stdout
  //   Use 'r' to count bytes read
  // Exit if there is a write error
  while( (s = read(sock, in_buf, BUF_SIZE)) > 0 ){
    if( write(1, in_buf, s) < 0 ){
      perror("receiver");
      exit(1);
    }
  }
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
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_protocol = IPPROTO_TCP;


  // TODO: Use getaddrinfo() to resolve hostname.
  int ec;
  if((ec = getaddrinfo(hostname, NULL, &hints, &result)) != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ec));
    exit(1);
  }


  // TODO: Properly set IP address and port in saddr
  saddr = (struct sockaddr_in*) result->ai_addr;
  saddr->sin_port = htons(port);
  printf("%s:%d\n", inet_ntoa(saddr->sin_addr), ntohs(saddr->sin_port));
  freeaddrinfo(result);

  // TODO: Open the socket (sock)
  if( (sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0 )
  {
    perror("socket: socket failed");
    exit(1);
  } 


  printf("Socket fd(%d)\n", sock);

  // TODO: Connect the socket
  if((ec = connect(sock, (struct sockaddr*)&saddr, sizeof(struct sockaddr))) < 0){
    fprintf(stderr, "connect: connection refused: %s\n", strerror(errno));
    close(sock);
    exit(1);
  }


  // TODO: Create the sender and receiver threads
  pthread_create(&send_thread, NULL, sender, NULL);
  pthread_create(&receive_thread, NULL, receiver, NULL);


  // TODO: Have the main thread wait on the sender and receiver threads
  pthread_join(send_thread, NULL);
  pthread_join(receive_thread, NULL);


  close(sock);

  exit(0);
}
