#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

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

	if(bind(diskr_soket, (const struct sockaddr*)&server, sizeof(server))<0)
	{
		printf("bind failed\n");
		close(diskr_soket);
		return 0;
	}

	char message_from_client[100];
	char message_to_client[100];

	struct sockaddr_in src_addr;

	while(1)
	{

		int adrr_len = sizeof(src_addr);

		if(recvfrom(diskr_soket, message_from_client, sizeof(message_from_client), 0, (struct sockaddr*)&src_addr, &adrr_len)<0)
		{
			printf("recvfrom failed\n");
			close(diskr_soket);
			return 0;
		}

		printf("message_from_client - %s\n", message_from_client);

		message_from_client[0]='0';

		if(sendto(diskr_soket, message_from_client, strlen(message_from_client), 0, (struct sockaddr*)&src_addr, sizeof(src_addr))<0)
		{
			printf("sendto failed\n");
			close(diskr_soket);
			return 0;
		}
	}

	close(diskr_soket);

	return 0;
}