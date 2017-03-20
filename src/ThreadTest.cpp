#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unistd.h>

class CTesta
{
public:
	CTesta() {}
	~CTesta() {}

	static void ThreadRun() {
		while(1) {
			std::cout << "thread test..." << std::endl;
			sleep(1);
		}
	}

	void CreateThread() {
		std::thread t1( &CTesta::ThreadRun );
		t1.join();
	}
};

int main() {
	CTesta tt();
	tt.CreateThread();
	return 1;
}
