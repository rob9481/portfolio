#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// Based on: https://stackoverflow.com/a/32593825
class ThreadPool {
public:
  ~ThreadPool();

  void start(unsigned numThreads = std::thread::hardware_concurrency());

  template <class F> void addJob(F f) {
    {
      std::lock_guard<std::mutex> lock(_mutex);
      _jobs.push(f);
    }
    _cv.notify_one();
  }

  int numJobs() const;

  void stop();

private:
  void loop();

private:
  std::atomic_bool _done = false;
  std::atomic_int _inProgress = false;
  std::condition_variable _cv;
  mutable std::mutex _mutex;
  std::queue<std::function<void()>> _jobs;
  std::vector<std::thread> _threads;
};

#endif // THREAD_POOL_H
