#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <functional>
#include <mutex>
#include <queue>
#include <semaphore>
#include <thread>

class ThreadPool {
    private:
        std::counting_semaphore<100> jobsAvailableSemaphore;
        std::mutex jobsQueueMtx;
        std::queue<std::function<void()>> jobs;
        std::vector<std::thread> threads;

        void threadWait() {
            while(true) {
                jobsAvailableSemaphore.acquire();
                jobsQueueMtx.lock();
                std::function<void()> job = jobs.front();
                jobs.pop();
                jobsQueueMtx.unlock();
                job();
            }
        }

    public:
        ThreadPool(int numThreads) :
                jobsAvailableSemaphore(0),
                jobs(std::queue<std::function<void()>>()),
                threads(std::vector<std::thread>()) {

            for(int i = 0; i < numThreads; i++) {
                threads.emplace_back(std::thread(&threadWait, this));
                threads.back().detach();
            }
        }

        void queueJob(const std::function<void()> &job) {
            jobsQueueMtx.lock();
            jobs.push(job);
            jobsAvailableSemaphore.release();
            jobsQueueMtx.unlock();
        }
};

#endif