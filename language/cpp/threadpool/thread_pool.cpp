#include "thread_pool.h"
#include "print.h"

ThreadPool::ThreadPool(const size_t thread_count) :
  thread_count_(thread_count),
  status_(Status::Ready)
{
  this->CreateThreads();
}

ThreadPool::~ThreadPool()
{
  this->cv_task_.notify_all();
  this->DestroyThreads();
}

void ThreadPool::SetMaxThreadCount(const size_t count)
{
  this->thread_count_ = count;
}

size_t ThreadPool::GetMaxThreadCount() const
{
  return this->thread_count_;
}

void ThreadPool::Start()
{
  this->status_.store(Status::Running, std::memory_order_release);
}

void ThreadPool::Abort()
{
  std::cout << "Abort" << std::endl;
  {
    std::lock_guard<std::mutex> locK_task(this->mu_task_);
    this->status_.store(Status::Aborted, std::memory_order_release);
  }
  this->cv_task_.notify_all();
  this->DestroyThreads();
}

void ThreadPool::Exec()
{
  while(true)
  {
    std::unique_lock<std::mutex> lock_task(this->mu_task_);
    std::atomic_thread_fence(std::memory_order_acquire);
    // this->WaitTask();
    this->cv_task_.wait(lock_task,
                        [this]()
                        {                          
                          std::cout << "wait : " << std::this_thread::get_id() << std::endl;
                          Status status = this->status_.load(std::memory_order_acquire);
                          std::cout << static_cast<int>(status) << std::endl;
                          return !this->tasks_.empty() ||
                                  status == Status::Aborted ||
                                  status == Status::Finished;
                        });

    // std::unique_lock<std::mutex> lock_task(this->mu_task_);
    Status status = this->status_.load(std::memory_order_relaxed);
    if(status == Status::Aborted || status == Status::Finished)
    {
      std::cout << "Aborted" << std::endl;
      break;
    }

    Task task;
    if(this->PopTask(task))
    {
      task();
    }
    else 
    {
      break;
    }
  }
  std::cout << "thread end : " << std::this_thread::get_id() << std::endl;
}

void ThreadPool::CreateThreads()
{
  this->threads_.clear();
  this->threads_.reserve(this->thread_count_);
  for(size_t count = 0; count < this->thread_count_; ++count)
  {
    this->threads_.emplace_back(&ThreadPool::Exec, this);
  }
}

void ThreadPool::DestroyThreads()
{
  for(std::thread& thread : this->threads_)
  {
    thread.join();
  }
}

void ThreadPool::SetTasks(std::queue<Task>&& tasks)
{
  {
    std::lock_guard<std::mutex> lock_task(this->mu_task_);
    this->tasks_ = std::move(tasks);
  }

  std::cout << "SetTasks" << std::endl;
  this->cv_task_.notify_all();
}

void ThreadPool::WaitTask()
{
  std::unique_lock<std::mutex> lock_task(this->mu_task_);
  this->cv_task_.wait(lock_task,
                      [this]()
                      {
                        std::cout << "wait : " << std::this_thread::get_id() << std::endl;
                        Status status = this->status_.load(std::memory_order_acquire);
                        std::cout << static_cast<int>(status) << std::endl;
                        return !this->tasks_.empty() ||
                                status == Status::Aborted ||
                                status == Status::Finished;
                      });
}

bool ThreadPool::PopTask(Task& task)
{
  std::lock_guard<std::mutex> lockTask(this->mu_task_);

  if(this->tasks_.empty()) return false;

  task = std::move(this->tasks_.front());
  this->tasks_.pop();

  return true;
}