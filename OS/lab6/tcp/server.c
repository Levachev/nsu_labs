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

	int diskr_soket, ret;

	struct sockaddr_in serverAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	diskr_soket = socket(AF_INET, SOCK_STREAM, 0);
	if(diskr_soket < 0){
		printf("Error socket\n");
		return 0;
	}

	//memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr=INADDR_ANY;

	ret = bind(diskr_soket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error bind");
		close(diskr_soket);
		return 0;
	}

	if(listen(diskr_soket, 10)==-1){
		printf("Error listen");
		close(diskr_soket);
		return 0;
	}

	int new_socket;
	struct sockaddr_in new_addr;

	while(1){
		new_socket = accept(diskr_soket, (struct sockaddr*)&new_addr, &addr_size);
		if(new_socket < 0){
			close(diskr_soket);
			return 0;
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));

		if((childpid = fork()) == 0){
			close(diskr_soket);

			while(1){
				recv(new_socket, buffer, 1024, 0);
				if(strcmp(buffer, ":exit") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));
					break;
				}
				else{
					printf("Client: %s\n", buffer);
					send(new_socket, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
				}
			}
		}
		close(new_socket);

	}

	close(new_socket);


	return 0;
}