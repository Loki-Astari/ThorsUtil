#ifndef THORSANVIL_UTIL_H
#define THORSANVIL_UTIL_H

#include <random>
#include <iterator>
#include <limits>

namespace ThorsAnvil
{
    namespace ThorsUtil
    {

using Size = std::pair<int, int>;
using Pos  = std::pair<int, int>;
using Delta= std::pair<float, float>;
using Distribution = std::uniform_int_distribution<int>;

inline Distribution getDist(int max)
{
    return Distribution{0, max - 1};
}

template<typename C, typename G>
inline auto getRandomContainerIterator(C& container, G& generator)
{
    if (container.empty())
    {
        return container.end();
    }

    using std::begin;
    using std::size;

    auto    pos     = begin(container);
    int     offset  = getDist(size(container))(generator);
    return std::next(pos, offset);
}

class IgnoreUntilNewLine
{
    public:
        friend std::istream& operator>>(std::istream& stream, IgnoreUntilNewLine& /*data*/)
        {
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return stream;
        }
};

class SkipEmptyLineToEnd
{
    public:
        friend std::istream& operator>>(std::istream& stream, SkipEmptyLineToEnd& /*data*/)
        {
            std::string     emptyLine;
            std::getline(stream, emptyLine);
            if (!emptyLine.empty())
            {
                stream.setstate(std::ios::badbit);
            }
            return stream;
        }
};
    }
}

#endif
