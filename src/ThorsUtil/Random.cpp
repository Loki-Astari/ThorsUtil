#include "Random.h"

using namespace ThorsAnvil::ThorsUtil;

std::time_t Random::initTime = 0;

std::time_t Random::getSeed()
{
    initTime = initTime == 0 ? time(nullptr) : initTime;
    return initTime;
}

void Random::defaltGeneratorSeedSet(std::time_t init)
{
    initTime = init;
}

std::default_random_engine& Random::getRandomGenerator()
{
    static std::default_random_engine   generator(static_cast<long>(getSeed()));
    return generator;
}
