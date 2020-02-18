#include "BackgroundWorker.h"

using namespace ThorsAnvil::ThorsUtil;

BackgroundWorker::BackgroundWorker()
    : finished(false)
    , haveWork(false)
    , background([worker = this](){worker->run();})
{
}

BackgroundWorker::~BackgroundWorker()
{
    // Make sure any waiting thread is release.
    // Make sure any running thread will exit when finished.
    {
        std::unique_lock<std::mutex> locker(lock);
        finished = true;

        conditionRemWork.notify_one();
    }

    // Wait for thread to finish before exiting
    background.join();
}

void BackgroundWorker::run()
{
    while (!finished)
    {
        auto task = getNextTask();
        if (!finished)
        {
            task();
        }


        std::unique_lock<std::mutex> locker(lock);
        haveWork = false;
        conditionAddWork.notify_one();
    }
}

std::function<void()> BackgroundWorker::getNextTask()
{
    std::unique_lock<std::mutex> locker(lock);
    conditionRemWork.wait(locker, [worker = this](){return worker->haveWork || worker->finished;});

    auto result = std::move(work);
    return result;
}

bool BackgroundWorker::hasWork() const
{
    return haveWork;
}

void BackgroundWorker::addWork(std::function<void()>&& task)
{
    std::unique_lock<std::mutex> locker(lock);
    conditionAddWork.wait(locker, [worker = this](){return !worker->haveWork;});

    work        = std::move(task);
    haveWork    = true;

    conditionRemWork.notify_one();
}
