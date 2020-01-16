/// @file
/// @brief Defines a macro that lets one easily define a new class and its
/// counters

#pragma once

#include "Counter.hpp"

/// @mainpage
///
/// @section intro_sec Introduction
///
/// Macro for easy counter definitions.
/// Use the macro to define a new class name and one or more counter names.
/// The macro will produce a class with the provided name.  The counters will
/// be part of an enum defined inside the class.
/// The main method get<>() retrieves a Count::Counter object corresponding to
/// the counter enum via the template parameter.
/// Each Count::Counter object will contain the counter name as a std::string
/// and the value of the counter.
/// A template variable for the counter enum value is used so the code can
/// perform static asserts and ensure no out-of-bounds access to the underlying
/// container.
///
/// Usage:
/// @code{.cpp}
/// DEFINE_COUNTERS(TestCounters, A, B, C)
/// TestCounters counters;
/// counters.get<TestCounters::A>() = 2;
/// counters.get<TestCounters::B>()++;
/// auto c = counters.get<TestCounters::C>();
/// std::cout << "Counter: " << c.Name() << "=" << c.Value();
/// @endcode
///
/// @section macro_sec Macro
///
/// #DEFINE_COUNTERS(CounterClassName, ...)
///
/// @section classes_sec Classes
///
/// Count::Counter

/// @def DEFINE_COUNTERS(CounterClassName, ...)
/// @brief Convenient macro that defines a class given as
///       the first argument and the counter names as
///       the remaining arguments.  Each counter is
///       defined in an enum inside the class and the
///       name of the counter is stored within
///       each Counter object
/// @note access a Count::Counter via CounterClassName::get<CounterEnumValue>()
#define DEFINE_COUNTERS(CounterClassName, ...)                        \
class CounterClassName                                                \
{                                                                     \
public:                                                               \
    enum CounterEnum { __VA_ARGS__, TotalCounters };                  \
    using Counter_t = Count::Counter<unsigned long long>;             \
    CounterClassName()                                                \
    {                                                                 \
        std::string str;                                              \
        std::stringstream ss(#__VA_ARGS__);                           \
        while(getline(ss, str, ','))                                  \
        {                                                             \
            str.erase(0, str.find_first_not_of(' '));                 \
            m_counters.emplace_back(Counter_t(str));                  \
        }                                                             \
    }                                                                 \
    size_t Size() const { return TotalCounters; }                     \
    void Reset() { for (auto& counter : m_counters) counter = 0; }    \
    template<CounterEnum index> Counter_t& get()                      \
    {                                                                 \
        static_assert(index < TotalCounters, "Counter out of range"); \
        return m_counters[index];                                     \
    }                                                                 \
protected:                                                            \
    std::vector<Counter_t> m_counters;                                \
}
