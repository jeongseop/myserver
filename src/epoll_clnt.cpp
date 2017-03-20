#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct _tmp
{
	unsigned short size;
	char id[13];
} tmp;

int main(int argc, char *argv[])
{
	int fd;
	struct sockaddr_in serv_adr;
	tmp packet;

	if((fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
	{
		std::cout << "socket() error!!" << std::endl;
		exit(1);
	}

	std::cout << "unsigned short size: " << sizeof(unsigned short) << std::endl;

	bzero((char *)&serv_adr, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_port = htons(15030);
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(fd, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) < 0)
	{
		std::cout << "connect() error!!" << std::endl;
		exit(1);
	}

	int loop = 0;
	std::ostringstream oss;
	int w_l, r_l;
	char buf[256];
	while(1)
	{
		packet.size = sizeof(tmp) - sizeof(unsigned short);
		memcpy(packet.id, "0000000000001", 13);
		w_l = write(fd, &packet, sizeof(packet));
		if(w_l <= 0)
		{
			std::cout << "write error..." << std::endl;
			continue;
		}
		std::cout << "write packet[" << sizeof(packet) << "], size[" << w_l << "]" << std::endl;
		char buf[14];
		strcpy(buf, packet.id);
		std::cout << "size:" << packet.size << ", id:" << buf << "..." << std::endl;

		tmp r_tmp;
		r_l = read(fd, &r_tmp, w_l);
		if(r_l <= 0)
		{
			std::cout << "read error..." << std::endl;
			continue;
		}
		bzero(buf, sizeof(buf));
		strcpy(buf, r_tmp.id);
		std::cout << "read packet[size:" << r_tmp.size << ", id:" << buf << "], size[" << r_l << "]" << std::endl;

		//std::cout << "3초 대기...." << std::endl;
		sleep(5);
		break;
	}
}
