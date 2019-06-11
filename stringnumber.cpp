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


//    if (lhs.size() < rhs.size()) {
//        fillInZeros(lhs, )
//    }

//    StringNumber result;
//    std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), result.begin(), [] () {});

    return StringNumber{};
}

StringNumber operator*(const StringNumber& lhs, const StringNumber& rhs)
{
    return StringNumber{};
}
}