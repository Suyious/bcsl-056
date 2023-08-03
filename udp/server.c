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
	socklen_t clientlen;
	struct sockaddr_in server_addr, client_addr;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		error_handle("socket() failed");
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		error_handle("bind() failed");
	}

	printf("UDP SERVER starting up...\n");

	int value[10];
	clientlen = sizeof(client_addr);
	if(recvfrom(sockfd, &value, sizeof(value), 0, (struct sockaddr *)&client_addr, &clientlen) < 0) {
		error_handle("recvfrom() failed");
	}

	int response = 1;
	for(int i = 0; i < 10; i++) {
		printf("multiplying... *%d", value[i]);
		response *= value[i];
	}
	if(sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_addr, clientlen) < 0) {
		error_handle("sendto() failed");
	}

	close(sockfd);
}
