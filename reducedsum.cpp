#include "reducedsum.h"

namespace scientific {
namespace {
template <class Type>
size_t getDimension10(Type number)
{
    size_t count = 0;
    while (true) {
        ++count;
        number /= 10;
        if (number == 0) {
            break;
        }
    }

    return count;
}
}

bool ReducedSumParams::isSmallDimension(size_t n, long int a, long int b)
{
    const size_t nDimension = getDimension10(n);
    const size_t aDimension = getDimension10(a);
    const size_t bDimension = getDimension10(b);
    const size_t upperBoundDimension = 3 * nDimension + aDimension + bDimension;
    // upper bound for int64_t summ dimension for given params
    const size_t maxDimension = std::numeric_limits<long int>::digits10;

    if (upperBoundDimension > maxDimension) {
        return false;
    }

    return true;
}

void ReducedSumParams::initSmallParams()
{
    for (size_t i = 0; i < m_n; ++i) {
        m_smallMParam.emplace_front(m_a * (m_n - i));
        m_smallNParam.emplace_front(m_b * (m_n - i - m_a));
    }
}

void ReducedSumParams::initBigParams()
{

}

void ReducedSumParams::init()
{
    if (m_small) {
        initSmallParams();
    } else {
        initBigParams();
    }
}

}
