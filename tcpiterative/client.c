#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define SERVER_IP "0.0.0.0"

void error_handle(char* message) {
	perror(message);
	exit(EXIT_FAILURE);
}

int main() {

	int sockfd;
	struct sockaddr_in server_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error_handle("socket() failed");
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) < 0) {
		error_handle("connect() failed");
	}

	int num;
	printf("Enter number: ");
	scanf("%d", &num);
	if(send(sockfd, &num, sizeof(int), 0) < 0) {
		error_handle("send() failed");
	}

	char buff[100];
	if(recv(sockfd, buff, sizeof(buff) - 1, 0) < 0) {
		error_handle("recv() failed");
	}

	printf("response: %s", buff);

	return 0;
}
