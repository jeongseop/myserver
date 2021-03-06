#ifndef _RING_BUFFER_HPP_
#define _RING_BUFFER_HPP_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>

/**
 * @brief 순환버퍼 클래스
 * @author Jeongseop Shim, jeongsub3312@naver.com
 * @date 2017-03-24
 * @version 1.0.0
 */
class CRingBuffer
{
private:
	char *m_buffer;
	int m_capacity;

	int m_head;
	int m_tail;

	int m_data_len;

public:
	CRingBuffer(int capacity_);

public:
	void create_buffer();
	void free_buffer();

	int get_capacity();
	int get_head();
	int get_tail();

	bool read_buffer(char *buf_, int len_);
	bool write_buffer(const char *data_, int len_);

private:
	int get_free_space();
};

#endif // _RING_BUFFER_HPP_ end
