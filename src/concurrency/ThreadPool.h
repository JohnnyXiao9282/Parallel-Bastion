#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace Concurrency {

class ThreadPool {
public:
    ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
    ~ThreadPool();
    
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    
private:
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;
    
    std::mutex m_queueMutex;
    std::condition_variable m_condition;
    bool m_stop;
};

} // namespace Concurrency
