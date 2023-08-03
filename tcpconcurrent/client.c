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
	struct sockaddr_in serveraddr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error_handle("socket() failed.");
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERVER_PORT);
	serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) < 0) {
		error_handle("connect() failed.");
	}

	int values[2];
    printf("Enter two integers: ");
    scanf("%d %d", &values[0], &values[1]);

	if(send(sockfd, values, sizeof(values), 0) < 0) {
		error_handle("send() failed.");
	}

	int swapped[2];
	if(recv(sockfd, swapped, sizeof(swapped), 0) < 0) {
		error_handle("recv() failed");
	}

	printf("Swapped Values %d %d", swapped[0], swapped[1]);
	close(sockfd);


	return 0;
}
