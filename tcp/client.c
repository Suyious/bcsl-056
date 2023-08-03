#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 8080

void error_handle(char* message) {
	perror(message);
	exit(EXIT_FAILURE);
}

int main() {

	int sockfd;
	struct sockaddr_in server_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error_handle("socket() failed.");
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		error_handle("connect() failed.");
	}

	char response[100];
	if(recv(sockfd, response, sizeof(response) - 1, 0) < 0) {
		error_handle("recv failed.");
	}
	printf("[LOG] Received: %s", response);

	return 0;
}
