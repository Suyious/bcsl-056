#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#define CLIENTPORT 8090

int main() {

	int sockfd;
	struct sockaddr_in local_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(CLIENTPORT);
	local_addr.sin_addr.s_addr = inet_addr("192.10.10.10");
	bzero(&(local_addr.sin_zero), 8);

	bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr));

    return 0;
}
