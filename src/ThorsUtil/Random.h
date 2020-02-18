#ifndef THORSANVIL_THORSUTIL_RANDOM_H
#define THORSANVIL_THORSUTIL_RANDOM_H

#include <random>
#include <ctime>

namespace ThorsAnvil
{
    namespace ThorsUtil
    {

class Random
{
    private:
        static std::time_t  initTime;
        static std::time_t  getSeed();
    public:
        static void defaltGeneratorSeedSet(std::time_t init);
        static std::default_random_engine&      getRandomGenerator();
};

    }
}

#endif
