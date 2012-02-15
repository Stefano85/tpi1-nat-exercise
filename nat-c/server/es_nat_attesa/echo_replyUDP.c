#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>

#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SERV_PORT   30000 
#define MAXLINE     1024

int main(int argc, char **argv) {
  int sockfd;
  socklen_t len;
  struct sockaddr_in addr;
  char buff[MAXLINE];
  char echo_replay[] = "Echo reply \n";	

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { /* crea il socket */
    perror("errore in socket");
    exit(1);
  }

  memset((void *)&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY); /* il server accetta pacchetti su una qualunque delle sue interfacce di rete */
  addr.sin_port = htons(SERV_PORT); /* numero di porta del server */

  /* assegna l'indirizzo al socket */
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("errore in bind");
    exit(1);
  }

  int i = 0; 

  while (1) {	
    len = sizeof(addr);
    printf("server in ricezione...\n");
    if ( (recvfrom(sockfd, buff, MAXLINE, 0, (struct sockaddr *)&addr, &len)) < 0) {
      perror("errore in recvfrom");
      exit(1);
    }
	printf("echo request ricevuta!\n");
	if(i>0) {
	   printf("attendo %d secondi prima di effettuare l'echo reply\n",178+i);    
	   sleep(178+i);
	   printf("attesa terminta! invio dell'echo reply in corso...\n");
	}
	
    if (sendto(sockfd, echo_replay, strlen(echo_replay), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
      perror("errore in sendto");
      exit(1);
    }
    printf("echo reply inviata.\n"); 	
    i+=1;
  }
  exit(0);
}
