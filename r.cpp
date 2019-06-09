#include "r.h"

namespace calculating {

bool RParams::isSmallDimension(size_t n, long int a, long int b)
{
    const size_t nDimension = getDimension(n);
    const size_t aDimension = getDimension(a);
    const size_t bDimension = getDimension(b);
    const size_t upperBoundDimension = 3 * nDimension + aDimension + bDimension;
    // upper bound for R dimension for given params
    const size_t maxDimension = std::numeric_limits<long int>::digits10;

    if (upperBoundDimension > maxDimension) {
        return false;
    }

    return true;
}

void RParams::initSmallParams()
{
    for (size_t i = 0; i < m_n; ++i) {
        m_smallMParam.emplace_front(m_a * (m_n - i));
        m_smallNParam.emplace_front(m_b * (m_n - i - m_a));
    }
}

void RParams::initBigParams()
{

}

void RParams::init()
{
    if (m_small) {
        initSmallParams();
    } else {
        initBigParams();
    }
}

}
