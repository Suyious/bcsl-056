#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080

void error_handle(char* message) {
		perror(message);
		exit(EXIT_FAILURE);
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void client_handle(int clientsockfd) {
	int values[2];

	if(recv(clientsockfd, values, sizeof(values), 0) < 0) {
		perror("recv() failed.");
		close(clientsockfd);
		return;
	}

	printf("Received %d, %d. Swapping...\n", values[0], values[1]);

	swap(&values[0], &values[1]);

	if(send(clientsockfd, values, sizeof(values), 0) < 0) {
		perror("send() failed");
	}

	close(clientsockfd);
}

int main() {

	int sockfd, clientsockfd, len;
	struct sockaddr_in server_addr, client_addr;

	if(( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0) {
		error_handle("socket() failed.");
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if( bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) < 0 ) {
		error_handle("bind() failed.");
	}

	if( listen(sockfd, 4) < 0 ) {
		error_handle("listen() failed.");
	}

	printf("Server listening on port %s:%d\n",inet_ntoa(server_addr.sin_addr), SERVER_PORT);

	while(1) {
		len = sizeof(client_addr);
		if ((clientsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &len)) < 0) {
			error_handle("accept() failed.");
		}

		printf("[LOG] new connection!\n");

		if(fork() == 0) {
			close(sockfd);
			client_handle(clientsockfd);
			exit(EXIT_SUCCESS);
		}

		close(clientsockfd); 	// from <unistd.h>
	}

	close(sockfd);

	return 0;
}
