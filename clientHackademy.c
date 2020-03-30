#include "wrapper.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int sockfd,connfd ,n;
	char buff[80];
	struct sockaddr_in servaddr;

	/* gestione errore */
	/*if (argc != 2) {
        fprintf(stderr,"usage: %s <IPaddress>\n",argv[0]);
        exit(1);
    }*/

	/* creazione socket */
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(27380);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* connessione al server */
	Connect(sockfd, &servaddr);

	/* lettura del Daytime */
	while (1)
	{
		// bzero(buff, sizeof(buff));
		memset(buff, 0, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while((buff[n++] = getchar()) != '\n');
		// printf("%s\n", buff);
		FullWrite(sockfd, buff, sizeof(buff));
		// bzero(buff, sizeof(buff));
		memset(buff, 0, sizeof(buff));
		FullRead(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0)
		{
			printf("Client Exit...\n");
			break;
		}
	}
	// close the socket
	close(sockfd);
}
