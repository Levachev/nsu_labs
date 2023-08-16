#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2000

int main(){

	int client_socket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket < 0){
		printf("Error socket");
		return 0;
	}

	//memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	ret = connect(client_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error connect");
		close(client_socket);
		return 0;
	}

	while(1){
		printf("Client: \t");
		scanf("%s", &buffer[0]);
		send(client_socket, buffer, strlen(buffer), 0);

		if(strcmp(buffer, ":exit") == 0){
			close(client_socket);
			printf("Disconnected");
			close(client_socket);
			return 0;
		}

		if(recv(client_socket, buffer, 1024, 0) < 0){
			printf("Error recv");
		}else{
			printf("Server: \t%s\n", buffer);
		}
	}

	return 0;
}