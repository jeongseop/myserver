#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

class CThreadpool
{
public:
	CThreadpool();
	~CThreadpool();

private:
	unsigned int worker_thread_cnt;
}

#endif
