#include "ThreadPool.h"

ThreadPool::~ThreadPool() { stop(); }

void ThreadPool::start(unsigned numThreads) {
  _done = false;
  _threads.reserve(numThreads);
  for (unsigned i = 0; i < numThreads; ++i) {
    _threads.emplace_back(&ThreadPool::loop, this);
  }
}

int ThreadPool::numJobs() const {
  std::lock_guard<std::mutex> lock(_mutex);
  return _jobs.size() + _inProgress;
}

void ThreadPool::stop() {
  _done = true;
  _cv.notify_all();
  for (auto &thread : _threads)
    thread.join();
}

void ThreadPool::loop() {
  while (true) {
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(_mutex);
      _cv.wait(lock, [&] { return !_jobs.empty() || _done; });
      if (_done) {
        return;
      }
      job = _jobs.front();
      _jobs.pop();
    }
    ++_inProgress;
    job();
    --_inProgress;
  }
}
