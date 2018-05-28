#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

#define BUFSIZE 1000

int main(int argc, char** argv){
	int client_sockfd;
	int len;
	struct sockaddr_in remote_addr;

	int sin_size;
	char buf[BUFSIZE];
	memset(&remote_addr, 0, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET; // IP Communications
	remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //local server
	remote_addr.sin_port = htons(8000); 

	/*IPv4, TCP-SOCK_STREAM, UDP-SOCK_DGRAM*/
	if((client_sockfd = socket(PF_INET, SOCK_STREAM, 0))<0){ 
		perror("socket error");
		return 1;
	}

	if(connect(client_sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr))<0){
		perror("connect error");
		return 1;
	}
	printf("connect to server/n");
	len = recv(client_sockfd, buf, BUFSIZE, 0);
	buf[len] = 0;
	printf("%s", buf);

	while(1){
		printf("Enter string to send");
		scanf("%s", buf);
		if(strcmp(buf, "quit") == 0){
			break;
		}
		len = send(client_sockfd, buf, strlen(buf), 0);
		len = recv(client_sockfd, buf, BUFSIZE, 0);
		buf[len] = 0;
		printf("recv: %s\n", buf);
	}

	close(client_sockfd);
	return 0;
}

