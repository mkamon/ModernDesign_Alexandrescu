#pragma once
#include <mutex>
namespace policy
{
    template <typename T>
    struct SingleThreadModel
    {
        class Lock
        {
        public:
            explicit Lock(T &){}
        };
    };

    template <typename T>
    struct MultiThreadModel
    {
        class Lock
        {
            std::mutex mutex;
        public:
            explicit Lock(T &)
            {
                mutex.lock();
            }
            ~Lock(){
                mutex.unlock();
            }
        };
    };
}
