#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void setnonblock(int fd)
{
	int flag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

int main(int argc, char *argv[]) {
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char buf[128];

	struct epoll_event event, ep_events[64];
	int epfd, event_cnt;

	if(argc != 2)
	{
		std::cout << "Usage : " << argv[0] << " <port>" << std::endl;
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	{
		std::cout << "bind error!!" << std::endl;
	}
	std::cout << "bind() complite!!" << std::endl;
	if(listen(serv_sock, 5) == -1)
	{
		std::cout << "listen error!!" << std::endl;
	}
	std::cout << "listen() complite!!" << std::endl;

	epfd = epoll_create(64);
	setnonblock(serv_sock);
	event.events = EPOLLIN;
	event.data.fd = serv_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

	while(1)
	{
		std::cout << "epoll_wait..." << std::endl;
		event_cnt = epoll_wait(epfd, ep_events, 64, -1);
		if(event_cnt == -1)
		{
			//error
			std::cout << "epoll_wait error!!" << std::endl;
			break;
		}
		std::cout << "event accept..." << std::endl;

		for(i=0; i<event_cnt; i++)
		{
			if(ep_events[i].data.fd == serv_sock)
			{
				adr_sz = sizeof(clnt_adr);
				clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
				setnonblock(clnt_sock);
				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
				std::cout << "connected client: " << clnt_sock << std::endl;
				continue;
			}

			str_len = read(ep_events[i].data.fd, buf, 128);
			if(str_len == 0) // close connection
			{
				epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
				close(ep_events[i].data.fd);
				std::cout << "closed client: " << ep_events[i].data.fd << std::endl;
				continue;
			}
			else if(str_len < 0)
			{
				if(errno == EAGAIN)
				{
					// wouldblock
					break;
				}
			}
			else
			{
				std::cout << "read packet fd[" << ep_events[i].data.fd << "], packet[" << buf << "], size[" << str_len << "]" << std::endl;

				write(ep_events[i].data.fd, buf, str_len);
			}
		}
	}

	close(serv_sock);
	close(epfd);
	return 0;
}
