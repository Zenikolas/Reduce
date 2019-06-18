#include "reducedsum.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <numeric>

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

bool ReducedSumParams::checkDimensionParams(size_t n, long int a, long int b)
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

bool ReducedSumParams::init()
{
    if (!checkDimensionParams(m_n, m_a, m_b)) {
        return false;
    }

    for (size_t i = 0; i < m_n; ++i) {
        m_mParam.emplace_front(m_a * (m_n - i));
        m_nParam.emplace_front(m_b * (m_n - i - m_a));
    }

    return true;
}

long int backwardReducedSum(const std::forward_list<long int>& lhs, const std::forward_list<long int>& rhs)
{
    if (rhs.empty()) {
        return 0;
    }

    std::forward_list<long int> tmp;
    for (auto& elem : rhs) {
        tmp.emplace_front(elem);
    }

    std::vector<long int> output;
    std::transform(lhs.begin(), lhs.end(), tmp.begin(), std::back_inserter(output), std::multiplies<>());
    return std::accumulate(output.begin(), output.end(), 0L);
}

}
