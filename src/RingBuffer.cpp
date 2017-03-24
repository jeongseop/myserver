#include "RingBuffer.hpp"

/**
 * @brief 생성자
 * @param capacity_ 순환버퍼의 크기
 */
CRingBuffer::CRingBuffer(int capacity_)
	: m_capacity(capacity_), m_head(0), m_tail(0), m_data_len(0)
{
}

/**
 * @brief 버퍼 생성 메소드
 */
void CRingBuffer::create_buffer()
{
	m_buffer = new char[m_capacity];
}

/**
 * @brief 버퍼 해제 메소드
 */
void CRingBuffer::free_buffer()
{
	delete[] m_buffer;
}


/**
 * @brief 순환버퍼의 크기 반환
 * @return int m_capacity
 */
int CRingBuffer::get_capacity()
{
	return m_capacity;
}

/**
 * @brief 순환버퍼의 head 위치 반환
 * @return int m_head
 */
int CRingBuffer::get_head()
{
	return m_head;
}

/**
 * @brief 순환버퍼의 tail 위치 반환
 * @return int m_tail
 */
int CRingBuffer::get_tail()
{
	return m_tail;
}

/**
 * @brief 버퍼에 저장된 메세지 읽기
 * @detail 버퍼에 저장된 내용중 지정된 길이만큼만 읽는다
 *         버퍼에 지정된 길이만큼의 데이터가 없으면 실패
 * @parameter buf_ 버퍼의 내용을 읽어올 char*
 * @parameter len_ 읽어올 길이
 * @return bool 성공:true,실패:false
 */
bool CRingBuffer::read_buffer(char *buf_, int len_)
{
	//읽을 데이터가 있는지 확인
	if(m_data_len < len_)
		return false;

	//1차로 읽을 데이터길이 셋팅
	int read_len = len_;
	int head = m_head;

	if(m_tail < m_head)
		read_len = m_capacity - m_head;

	memcpy(buf_, &m_buffer[head], read_len);
	head += read_len;
	if(head >= m_capacity)
		head -= m_capacity;

	if(read_len < len_)
	{
		int second_len = len_ - read_len;

		memcpy(&buf_[read_len], &m_buffer[head], second_len);
		head += second_len;
		if(head >= m_capacity)
			head -= m_capacity;
	}

	m_data_len -= len_;
	m_head = head;

	return true;
}

/**
 * @brief 버퍼에 메세지 저장
 * @parameter data_ 저장될 메세지
 * @parameter len_ 메세지 길이
 * @return bool 성공:true,실패:false
 */
bool CRingBuffer::write_buffer(const char *data_, int len_)
{
	//여유공간 확인
	if((m_capacity - m_data_len) < len_)
		return false;

	//1차로 입력할 길이 셋팅
	int write_len = len_;
	int tail = m_tail;
	if((tail >= m_head) && (m_capacity - tail) < len_)
		write_len = m_capacity - tail;

	//1차 데이터 카피
	std::memcpy(&m_buffer[tail], data_, write_len);
	tail += write_len;
	if(tail >= m_capacity)
		tail = tail - m_capacity;

	//버퍼에 입력해야할 데이터가 남아있으면
	if(write_len < len_)
	{
		//남은 길이만큼 추가로 카피
		int second_len = len_ - write_len;
		memcpy(&m_buffer[tail], &data_[write_len], second_len);
		tail += second_len;
		if(tail >= m_capacity)
			tail -= m_capacity;
	}

	m_data_len += len_;
	m_tail = tail;

	return true;
}
