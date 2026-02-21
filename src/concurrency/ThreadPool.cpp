#include "ThreadPool.h"

namespace Concurrency {

ThreadPool::ThreadPool(size_t numThreads)
    : m_stop(false)
{
    (void)numThreads;
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_stop = true;
    }
    m_condition.notify_all();
    
    for (std::thread& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

} // namespace Concurrency
