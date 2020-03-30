/**
 * Server comunicante col Client. 
 * Chat, scambio di messaggi a turno.
 */

#include "wrapper.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
	int listenfd, connfd; /* descrittori */
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr; /* socket */
	char buff[80];
	int n, i;


	/* creazione socket */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
		printf("Errore setsockopt");

	/* indirizzo del server */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(27380);

	/* assegnazione indirizzo */
	Bind(listenfd, &servaddr);
	/* messa in ascolto */
	Listen(listenfd, 1024) /*Backlog*/;

	len = sizeof(cliaddr);

	/* accettazione nuova richiesta */
	connfd = Accept(listenfd, &cliaddr, &len);

	/* esecuzione server */
	while (1)
	{
		memset(buff, 0, sizeof(buff));
		FullRead(connfd, buff, sizeof(buff));
		printf("From client: %s\n To client : ", buff);
		memset(buff, 0, sizeof(buff));
		n=0;
		while ((buff[n++] = getchar() ) != '\n');
		FullWrite(connfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}


	}
	close(listenfd);
}