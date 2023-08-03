#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define SERVER_PORT 8080

void error_handle(char* message) {
	perror(message);
	exit(EXIT_FAILURE);
}

char* time_handle() {
	time_t t;
	time(&t);

	return ctime(&t);
}

int main() {

	int sockfd, clientsockfd, len;
	struct sockaddr_in server_addr, client_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error_handle("socket() failed.");
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0) {
		error_handle("bind() failed.");
	}

	if(listen(sockfd, 5) < 0) {
		error_handle("listen() failed.");
	}

	printf("listening on %s:%d\n", inet_ntoa(server_addr.sin_addr), SERVER_PORT);

	len = sizeof(client_addr);
	if((clientsockfd = accept(sockfd, (struct sockaddr * )&client_addr, &len)) < 0) {
		error_handle("accept() failed.");
	}

	char* time_n = time_handle();
	if(send(clientsockfd, time_n, strlen(time_n), 0) < 0) {
		error_handle("send() failed.");
	}

	close(clientsockfd);
	close(sockfd);

	return 0;
}
