#ifndef R_R_H
#define R_R_H

#include <unistd.h>
#include <limits>
#include <forward_list>
#include <string>
#include <numeric>

namespace scientific {
class ReducedSumParams {
public:
    using SmallDimensionList = std::forward_list<long int>;
    using BigDimensionList = std::forward_list<std::string>;
private:
    size_t m_n;
    long int m_a;
    long int m_b;
    bool m_small;
    SmallDimensionList m_smallNParam;
    SmallDimensionList m_smallMParam;
    BigDimensionList m_bigNParam;
    BigDimensionList m_bigMParam;
    BigDimensionList m_bigList;

    bool isSmallDimension(size_t n, long int a, long int b);
    void initSmallParams();
    void initBigParams();
public:
    ReducedSumParams(size_t n, long int a, long int b) : m_n(n), m_a(a), m_b(b),
    m_small(isSmallDimension(n, a, b)) {}

    void init();

    const SmallDimensionList& getSmallDimensionNParam() const { return m_smallNParam; }
    const SmallDimensionList& getSmallDimensionMParam() const { return m_smallMParam; }
    const BigDimensionList& getBigDimensionNParam() const { return m_bigNParam; }
    const BigDimensionList& getBigDimensionMParam() const { return m_bigMParam; }

    bool isSmallDimension() const { return m_small; }
};

template <class Type>
Type backwardReducedSum(const std::forward_list<Type>& lhs, const std::forward_list<Type>& rhs)
{
    if (rhs.empty()) {
        return Type{};
    }

    std::forward_list<Type> tmp;
    for (auto& elem : rhs) {
        tmp.emplace_front(elem);
    }

    return std::transform_reduce(lhs.begin(), lhs.end(), tmp.begin(), 0);
}

}

#endif // R_R_H
