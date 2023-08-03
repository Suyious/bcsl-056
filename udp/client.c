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

	int sockfd, len;
	struct sockaddr_in server_addr;

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		error_handle("socket() failed");
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

	int value[10];
	printf("Enter 10 numbers: ");
	for(int i = 0; i < 10; i++) {
		scanf("%d", &value[i]);
	}
	len = sizeof(server_addr);

	if(sendto(sockfd, &value, sizeof(int), 0, (struct sockaddr *)&server_addr, len) < 0) {
		error_handle("sendto() failed");
	}

	int response;
	if(recvfrom(sockfd, &response, sizeof(int), 0, (struct sockaddr *)&server_addr, &len) < 0) {
		error_handle("recvfrom() failed");
	}
	printf("%d", response);

}
