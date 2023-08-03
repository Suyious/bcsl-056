#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 8080

void error_handle(char* message) {
	perror(message);
	exit(EXIT_FAILURE);
}

int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) if (num % i == 0) return 0;
    return 1;
}

int main() {

	int sockfd, clientsockfd, len;
	struct sockaddr_in server_addr, client_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error_handle("socket() failed");
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) < 0) {
		error_handle("bind() failed");
	}

	if(listen(sockfd, 5) < 0) {
		error_handle("listen() failed");
	}

	printf("listening on %s:%d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

	while(1) {
		len = sizeof(client_addr);
		if((clientsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &len)) < 1) {
			error_handle("accept() failed");
		}

		printf("[LOG] new connection\n");

		int recvn;
		if(recv(clientsockfd, &recvn, sizeof(recvn), 0) < 0) {
			error_handle("recv() failed.");
		}

		int status = isPrime(recvn);
		char* response = status == 1 ? "prime" : "non-prime";

		if(send(clientsockfd, response, strlen(response), 0) < 0) {
			error_handle("send() failed");
		}

		close(clientsockfd);
	}

	close(sockfd);

	return 0;
}
