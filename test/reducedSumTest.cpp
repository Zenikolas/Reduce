#include "reducedsum.h"

#include <gtest/gtest.h>

TEST(ReducedSumTest, empty)
{
    std::forward_list<long int> n;

    long int r = scientific::backwardReducedSum(n, n);
    ASSERT_EQ(r, 0);
}

TEST(ReducedSumTest, one)
{
    std::forward_list<long int> n = {3};
    std::forward_list<long int> m = {14};

    long int r = scientific::backwardReducedSum(n, m);
    ASSERT_EQ(r, 42);
}

TEST(ReducedSumTest, null)
{
    std::forward_list<long int> n = {3, 23, 231, 123123, 22};
    std::forward_list<long int> m = {0, 0, 0, 0, 0};

    long int r = scientific::backwardReducedSum(n, m);
    ASSERT_EQ(r, 0);
}

TEST(ReducedSumTest, ladder)
{
    std::forward_list<long int> n;
    std::forward_list<long int> m;
    for (size_t i = 0; i < 9; ++i) {
        n.emplace_front(i + 1);
        m.emplace_front(10 - i - 1);
    }

    long int expected_r = 0;
    for (size_t i = 0; i < 9; ++i) {
        expected_r += (i + 1) * (i + 1);
    }

    long int r = scientific::backwardReducedSum(n, m);
    ASSERT_EQ(r, expected_r);
}

TEST(ReducedSumTest, minus)
{
    constexpr long int size = 10;
    std::forward_list<long int> n;
    std::forward_list<long int> m;
    for (size_t i = 0; i < size; ++i) {
        n.emplace_front(size - i);
        m.emplace_front(size / 2 - i);
    }


    long int expected_r = 0;
    for (size_t i = 0; i < size; ++i) {
        expected_r += (size - i) * ( - size / 2 + 1 + i);
    }

    long int r = scientific::backwardReducedSum(n, m);
    ASSERT_EQ(r, expected_r);
}