#ifndef THORSANVIL_THORSUTL_BACKGROUND_H
#define THORSANVIL_THORSUTL_BACKGROUND_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace ThorsAnvil
{
    namespace ThorsUtil
    {

class BackgroundWorker
{
        bool                    finished;
        bool                    haveWork;
        std::mutex              lock;
        std::condition_variable conditionAddWork;
        std::condition_variable conditionRemWork;
        std::function<void()>   work;
        std::thread             background;

        void                    run();
        std::function<void()>   getNextTask();

    public:
         BackgroundWorker();
        ~BackgroundWorker();

        bool hasWork() const;
        void addWork(std::function<void()>&& task);
};

    }
}

#endif
