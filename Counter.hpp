/// @file
/// @brief Defines the Count::Counter class
#pragma once

#include <string>

namespace Count
{
/// @brief Class that contains a counter and a name
template<typename CounterValueType>
class Counter
{
public:
    /// @brief Constructor
    /// @param name sets the name of the counter
    Counter(const std::string& name)
        : m_name(name), m_value(0) { }
    /// @brief Retrieves the name of the counter
    std::string Name() const
    {
        return m_name;
    }
    /// @brief Retrieves the value of the counter
    CounterValueType Value() const
    {
        return m_value;
    }
    /// @brief Retrieves the value of the counter
    operator CounterValueType() const
    {
        return m_value;
    }
    /// @brief assignement operator
    /// @param value is the new value for the counter
    Counter& operator=(CounterValueType value)
    {
        m_value = value;
        return *this;
    }
    /// @brief increment by the specified m_value
    /// @param value is how much to increase the counter by
    Counter& operator+=(CounterValueType value)
    {
        m_value += value;
        return *this;
    }
    /// @brief pre-increment operator
    Counter& operator++()
    {
        m_value += 1;
        return *this;
    }
    /// @brief post-increment operator
    Counter operator++(int)
    {
        Counter tmp(*this);
        operator++();
        return tmp;
    }
    /// @brief equality operator
    bool operator==(const Counter& value) const
    {
        return m_name == value.m_name && m_value == value.m_value;
    }
private:
    /// @brief the name of the counter
    std::string m_name;
    /// @brief the value of the counter
    CounterValueType m_value;
};

} // namespace Count
