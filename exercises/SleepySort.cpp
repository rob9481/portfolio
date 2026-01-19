// sleep sort
// https://interviewing.io/mocks/square-python-threaded-order-of-execution
#include <future>
#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>

void waitThenPrint(int time) {
	sleep(time);
	std::cout << time << '\n';
};

void thread_sol(const std::vector<int> times) {
	std::vector<std::thread> threads;
	threads.reserve(times.size());

	for (const int time : times) {
		threads.push_back(std::thread(&waitThenPrint, time));
	}

	for (auto &thread : threads) {
		thread.join();
	}

	std::cout << std::flush;
}

void future_sol(const std::vector<int> times) {
	std::vector<std::future<void>> futures;
	futures.reserve(times.size());

	for (const auto &time : times) {
		futures.push_back(std::async(&waitThenPrint, time));
	}

	for (const auto &future : futures) {
		future.wait();
	}

	std::cout << std::flush;
}

int main() {
	std::vector<int> times{3,1,5,4,2};
	for (int i = 1000000; i > 5; --i) {
		times.push_back(i);
	}
	//thread_sol(times);
	future_sol(times);

	return 0;
}
