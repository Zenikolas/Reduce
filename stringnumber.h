#ifndef STRINGNUMBER_H
#define STRINGNUMBER_H

#include <string>

namespace scientific {
class StringNumber{
    std::string m_number;
public:
    // CREATORS
    StringNumber() = default;
    explicit StringNumber(const std::string& number) : m_number(number) {}
    explicit StringNumber(const char* number) : m_number(number) {}
    StringNumber(const StringNumber&) = default;
    StringNumber(StringNumber&&) = default;
    StringNumber& operator=(const StringNumber&) = default;
    StringNumber& operator=(StringNumber&&) = default;

    bool isNull() const;
    size_t size() const { return m_number.size(); }
    auto begin() const { return m_number.begin(); }
    auto cbegin() const { return m_number.cbegin(); }
    auto end() const { return m_number.end(); }
    auto cend() const { return m_number.cend(); }


};

StringNumber operator+(const StringNumber& lhs, const StringNumber& rhs);
StringNumber operator*(const StringNumber& lhs, const StringNumber& rhs);

}

#endif // STRINGNUMBER_H
