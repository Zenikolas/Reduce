#ifndef SCIENTIFIC_REDUCEDSUM_H
#define SCIENTIFIC_REDUCEDSUM_H

#include <unistd.h>
#include <forward_list>

namespace scientific {
class ReducedSumParams {
private:
    size_t m_n;
    long int m_a;
    long int m_b;
    std::forward_list<long int> m_nParam;
    std::forward_list<long int> m_mParam;

    bool checkDimensionParams(size_t n, long int a, long int b);
public:
    ReducedSumParams(size_t n, long int a, long int b) : m_n(n), m_a(a), m_b(b) {}

    bool init();

    const std::forward_list<long int>& getNParam() const { return m_nParam; }
    const std::forward_list<long int>& getMParam() const { return m_mParam; }
};

long int backwardReducedSum(const std::forward_list<long int>& lhs, const std::forward_list<long int>& rhs);


}

#endif // SCIENTIFIC_REDUCEDSUM_H
