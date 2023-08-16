#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 100

int main()
{
	int diskr_soket;
	if ((diskr_soket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))<0)
	{
		printf("socket creation failed\n");
		return 0;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(2000);

	char message_from_server[100];
	char message_to_server[100];

	int n;
	while((n = read(fileno(stdin), message_to_server, BUFFER_SIZE))>0)
	{
		/*message_to_server[0]='4';
		message_to_server[1]='5';
		message_to_server[2]='6';
		message_to_server[3]='7';
		message_to_server[4]='\0';*/

		if(sendto(diskr_soket, message_to_server, strlen(message_to_server), 0, (struct sockaddr*)&server, sizeof(server))<0)
		{
			printf("sendto failed\n");
			close(diskr_soket);
			return 0;
		}

		int adrr_len = sizeof(server);

		if(recvfrom(diskr_soket, message_from_server, sizeof(message_from_server), 0, (struct sockaddr*)&server, &adrr_len)<0)
		{
			printf("recvfrom failed\n");
			close(diskr_soket);
			return 0;
		}

		printf("message_from_server - %s\n", message_from_server);
	}

	close(diskr_soket);

	return 0;
}