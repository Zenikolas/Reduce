#include "stringnumber.h"

namespace scientific {
bool StringNumber::isNull() const
{
    bool isNull = true;
    for (auto& digit : m_number) {
        if (digit != '0') {
            isNull = false;
            break;
        }
    }

    return isNull;
}

StringNumber operator+(const StringNumber& lhs, const StringNumber& rhs)
{
    if (lhs.isNull() || rhs.isNull()) {
        return StringNumber("0");
    }


    std::string::const_iterator shortBegin;
    std::string::const_iterator shortEnd;
    std::string::const_iterator longBegin;
    std::string::const_iterator longBeginAppend;
    std::string::const_iterator longEnd;

    if (lhs.size() < rhs.size()) {
        shortBegin = lhs.begin();
        shortEnd = lhs.end();
        longBegin = rhs.begin();
        longBeginAppend = longBegin + lhs.size();
        longEnd = rhs.end();
    } else {
        shortBegin = rhs.begin();
        shortEnd = rhs.end();
        longBegin = lhs.begin();
        longBeginAppend = longBegin + rhs.size();
        longEnd = lhs.end();
    }

    StringNumber result;
    bool shift = false;
    std::transform(shortBegin, shortEnd, longBegin, std::back_inserter(result),
                   [&shift](char clhs, char crhs) {
                       unsigned int sum = clhs + crhs - '0';
                       if (shift) {
                           ++sum;
                       }

                       if (sum > '9') {
                           sum -= 10;
                           shift = true;
                       } else {
                           shift = false;
                       }

                       return (char)sum;
                   });

    for (auto it = longBeginAppend;it != longEnd; ++it) {
        result.push_back(*it);
        if (shift) {
            result.back()++;
            shift = false;
        }
    }

    std::reverse(result.begin(), result.end());

    return StringNumber{};
}

StringNumber operator*(const StringNumber& lhs, const StringNumber& rhs)
{
    return StringNumber{};
}
}