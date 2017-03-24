#include <iostream>
#include <cstring>
#include "Log.hpp"
#include "RingBuffer.hpp"

int main()
{
	char test_buf[1024];

	const std::string t_msg = "test11tteess182349";
	std::cout << "test" << std::endl;

	CRingBuffer c_rb(128);
	c_rb.create_buffer();

	for(int i=0; i<10; i++)
	{
		c_rb.write_buffer(t_msg.c_str(), t_msg.size());
		LOG_INFO << "write message..";
		LOG_INFO << "head pt: " << c_rb.get_head() << ", tail pt: " << c_rb.get_tail();

		bzero(test_buf, sizeof(test_buf));
		c_rb.read_buffer(test_buf, t_msg.size());
		LOG_INFO << "read message: " << test_buf;
		LOG_INFO << "head pt: " << c_rb.get_head() << ", tail pt: " << c_rb.get_tail();
	}

	c_rb.free_buffer();
	return 0;
}
