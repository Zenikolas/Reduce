#include "stringnumber.h"
#include <iostream>
#include <algorithm>

namespace scientific {
    namespace {
        bool isLessModule(const StringNumber &lhs, const StringNumber &rhs) {
            size_t lsize = lhs.size();
            size_t rsize = rhs.size();
            auto lit = lhs.cbegin();
            auto rit = rhs.cbegin();

            if (lhs.isSigned()) {
                --lsize;
                ++lit;
            }

            if (rhs.isSigned()) {
                --rsize;
                ++rit;
            }

            if (lsize < rsize) {
                return true;
            } else if (rsize < lsize) {
                return false;
            }

            for (; lit != lhs.cend(); ++lit, ++rit) {
                if (*lit < *rit) {
                    return true;
                } else if (*rit < *lit) {
                    return false;
                }
            }

            return false;
        }

        void initBinaryOperandBounds(std::string::const_reverse_iterator &shortBegin,
                                     std::string::const_reverse_iterator &shortEnd,
                                     std::string::const_reverse_iterator &longBegin,
                                     std::string::const_reverse_iterator &longBeginAppend,
                                     std::string::const_reverse_iterator &longEnd,
                                     const StringNumber &lhs,
                                     const StringNumber &rhs) {
            if (isLessModule(lhs, rhs)) {
                shortBegin = lhs.crbegin();
                shortEnd = lhs.crend();
                longBegin = rhs.crbegin();
                longBeginAppend = longBegin + lhs.size();
                if (lhs.isSigned()) {
                    --shortEnd;
                    --longBeginAppend;
                }
                longEnd = rhs.crend();
                if (rhs.isSigned()) {
                    --longEnd;
                }
            } else {
                shortBegin = rhs.crbegin();
                shortEnd = rhs.crend();
                longBegin = lhs.crbegin();
                longBeginAppend = longBegin + rhs.size();
                if (rhs.isSigned()) {
                    --shortEnd;
                    --longBeginAppend;
                }
                longEnd = lhs.crend();
                if (lhs.isSigned()) {
                    --longEnd;
                }
            }
        }
    }

    bool StringNumber::isNull() const {
        bool isNull = true;
        for (auto &digit : m_number) {
            if (digit != '0') {
                isNull = false;
                break;
            }
        }

        return isNull;
    }

    void StringNumber::initNumber(const std::string &number) {
        if (number.front() == '+') {
            m_isSigned = true;
        } else if (number.front() == '-') {
            m_isPositive = false;
            m_isSigned = true;
        }
    }

    void StringNumber::normalize()
    {
        m_number.erase(std::find_if(m_number.rbegin(), m_number.rend(),
                               [](char ch) {
                                   return ch != '0';
                               }).base(), m_number.end());

        if (m_number.empty()) {
            m_number.push_back('0');
        }
    }

    StringNumber operator+(const StringNumber &lhs, const StringNumber &rhs) {
        if (lhs.isNull()) {
            return rhs;
        }
        if (rhs.isNull()) {
            return lhs;
        }

        std::string::const_reverse_iterator shortBegin;
        std::string::const_reverse_iterator shortEnd;
        std::string::const_reverse_iterator longBegin;
        std::string::const_reverse_iterator longBeginAppend;
        std::string::const_reverse_iterator longEnd;
        initBinaryOperandBounds(shortBegin, shortEnd, longBegin,
                                longBeginAppend, longEnd, lhs, rhs);

        bool shift = false;
        bool negative = false;
        bool isSum = lhs.isPositive() == rhs.isPositive();
        auto sumSymbolicDigits = [&shift, &negative, isSum](char lch, char rch) {
            int sum{};
            if (isSum) {
                sum = rch + lch;
            } else {
                sum = rch - lch;
            }

            if (shift && !negative) {
                ++sum;
            } else if (shift && negative) {
                --sum;
            }

            sum %= '0';
            sum += '0';
            if (sum > '9') {
                sum -= 10;
                shift = true;
                negative = false;
            } else if (sum < '0') {
                sum += 10;
                shift = true;
                negative = true;
            } else {
                negative = false;
                shift = false;
            }

            return (char) sum;
        };

        StringNumber result;
        std::transform(shortBegin, shortEnd, longBegin, std::back_inserter(result),
                       sumSymbolicDigits);

        for (auto it = longBeginAppend; it != longEnd; ++it) {
            int sum = *it;
            if (shift && !negative) {
                ++sum;
            } else if (shift && negative) {
                --sum;
            }

            if (sum < '0') {
                sum += 10;
                shift = true;
                negative = true;
            } else if (sum > '9') {
                sum -= 10;
                shift = true;
                negative = false;
            } else {
                shift = false;
                negative = false;
            }

            result.push_back(sum);
        }

        if (shift) {
            result.push_back('1');
        }

        if (!lhs.isPositive() && isLessModule(rhs, lhs)) {
            negative = true;
        } else if (!rhs.isPositive() && isLessModule(lhs, rhs)) {
            negative = true;
        }

        if (negative || (!lhs.isPositive() && !rhs.isPositive())) {
            result.push_back('-');
        }

        result.normalize();
        std::reverse(result.begin(), result.end());

        return result;
    }

    StringNumber operator*(const StringNumber &lhs, const StringNumber &rhs) {
        if (lhs.isNull() || rhs.isNull()) {
            return StringNumber{};
        }

        std::string::const_reverse_iterator shortBegin;
        std::string::const_reverse_iterator shortEnd;
        std::string::const_reverse_iterator longBegin;
        std::string::const_reverse_iterator longBeginAppend;
        std::string::const_reverse_iterator longEnd;
        initBinaryOperandBounds(shortBegin, shortEnd, longBegin,
                                longBeginAppend, longEnd, lhs, rhs);


        return StringNumber{};
    }

    std::ostream &operator<<(std::ostream &os, const
    StringNumber &number) {
        for (auto &sym : number) {
            os << sym;
        }

        return os;
    }
}
