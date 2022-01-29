#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <atomic>
#include <functional>
#include <condition_variable>

#include "task.h"

class ThreadPool
{
public:
  enum class Status
  {
    Ready,
    Running,
    Aborted,
    Finished
  };
  using Task = std::function<void()>;
public:
  ThreadPool(const size_t thread_count = std::thread::hardware_concurrency());
  ~ThreadPool();

  // not copyable
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  void SetMaxThreadCount(const size_t size);
  size_t GetMaxThreadCount() const;
  void SetTasks(std::queue<Task>&& tasks);
  void Start();
  void Abort();

private:
  void Exec();
  void CreateThreads();
  void DestroyThreads();
  void WaitTask();
  bool PopTask(Task& task);

private:
  size_t thread_count_ = std::thread::hardware_concurrency();
  std::vector<std::thread> threads_;

  std::queue<Task> tasks_;
  std::mutex mu_task_;
  
  std::atomic<Status> status_;
  std::mutex mu_status_;
  std::condition_variable cv_status_;
};

#endif // _THREAD_POOL_H_