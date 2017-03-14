#ifndef _PACKET_HPP_
#define _PACKET_HPP_

typedef struct _header
{
	unsigned short size;
	char protocol_id[2]; // RQ : Request	- Clnt => Serv		요청
						 // RS : Response	- Serv => Clnt		응답
						 // NF : Notify		- Serv => Clnt(Only)통지
						 // CM : Command	- Serv => Clnt(Only)명령
} header;

#endif // _PACKET_HPP_ end
