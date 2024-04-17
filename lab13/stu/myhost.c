#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char *argv[]){
  // see if there are enough arguments
  //if(argc != 2)
  //{
  //  fprintf(stderr, "no domain name provided\n");
  //  exit(1);
  //}


  struct addrinfo *result;		// to store results
  struct addrinfo *cur_result;    // to store results
  struct addrinfo hints;			// to indicate information we want
  struct sockaddr_in *saddr;		// to reference address (IPv4)
  int s; 							// for error checking


  //TODO: Complete the lab
  //
  // Outline:
  //   - set up the hints
  //   - perform the getaddrinfo()
  //   - iterate over the results
  //   - print the resolved ip address
  //   - clean up the results with freaddrinfo()inet_ntop(AF_INET6, (const void *)&saddr->sin_addr, NULL, 0)
  
  // set up the hints
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_protocol = IPPROTO_TCP;

  // perform the getaddrinfo
  if( (s = getaddrinfo(argv[1], NULL, &hints, &result)) )
  {
    fprintf(stderr, "getaddrinfo: %s\n" , gai_strerror(s));
    exit(1);
  }

  // iterator over the results
  cur_result = result;
  while( cur_result != NULL )
  {
    //if(cur_result->ai_protocol == IPPROTO_TCP)
    //{
      saddr = (struct sockaddr_in*)cur_result->ai_addr;
      if(cur_result->ai_family == AF_INET)
      {
        // print the resolved ip address
        printf("%s has address %s\n", argv[1], inet_ntoa(saddr->sin_addr));
      }
    //}
    cur_result = cur_result->ai_next;
  }

  // clean up the results with freeaddrinfo
  freeaddrinfo(result);

  // do it for IPv6
  // set up the hints
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET6;
  hints.ai_protocol = IPPROTO_TCP;

  // perform the getaddrinfo
  if( (s = getaddrinfo(argv[1], NULL, &hints, &result)) )
  {
    fprintf(stderr, "getaddrinfo: %s\n" , gai_strerror(s));
    exit(1);
  }

  // iterator over the results
  cur_result = result;
  while( cur_result != NULL )
  {
    //if(cur_result->ai_protocol == IPPROTO_TCP)
    //{
      struct sockaddr_in6 saddr6;
      memcpy(&saddr6, cur_result->ai_addr, sizeof(struct sockaddr_in6));
      
      if(cur_result->ai_family == AF_INET6)
      {
        char ipv6[30];
        inet_ntop(AF_INET6, (const void *)&saddr6.sin6_addr, ipv6, 30);
        if(ipv6 != NULL)
          printf("%s has IPv6 address %s\n", argv[1], ipv6);
      }
    //}
    cur_result = cur_result->ai_next;
  }

  // clean up the results with freeaddrinfo
  freeaddrinfo(result);

  return 0;

}
