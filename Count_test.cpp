#include "DefineCounters.hpp"
#include "gtest/gtest.h"

namespace // anonymous
{

template <typename T>
class CounterTest : public ::testing::Test
{
public:
    typedef Count::Counter<T> Counter;
};
using CounterTestTypes = ::testing::Types<
    char, unsigned char,
    short, unsigned short,
    int, unsigned int,
    long int, unsigned long int,
    size_t>;
TYPED_TEST_SUITE(CounterTest, CounterTestTypes);

TYPED_TEST(CounterTest, Constructor)
{
    std::string expectedCounterName = "Test Counter Name";
    typename TestFixture::Counter counter(expectedCounterName);
    EXPECT_EQ(counter, 0);
    EXPECT_EQ(counter.Name(), expectedCounterName);
}

TYPED_TEST(CounterTest, PostIncrement)
{
    typename TestFixture::Counter counter("Test");
    EXPECT_EQ(counter++, 0);
    EXPECT_EQ(counter++, 1);
    EXPECT_EQ(counter++, 2);
}

TYPED_TEST(CounterTest, PreIncrement)
{
    typename TestFixture::Counter counter("Test");
    EXPECT_EQ(++counter, 1);
    EXPECT_EQ(++counter, 2);
    EXPECT_EQ(++counter, 3);
}

TYPED_TEST(CounterTest, operator_plus_equal)
{
    typename TestFixture::Counter counter("Test");
    EXPECT_EQ(counter += 10, 10);
}

TYPED_TEST(CounterTest, operator_assignment)
{
    typename TestFixture::Counter counter("Test");
    counter = 123;
    EXPECT_EQ(counter, 123);
}


DEFINE_COUNTERS(TestCounters, A,
    B,     C,   TestCounterD   );
TEST(DefineCounters, ConstructorSizeName)
{
    TestCounters counters;
    EXPECT_EQ(counters.Size(), 4);
    EXPECT_EQ(counters.get<TestCounters::A>(), 0);
    EXPECT_EQ(counters.get<TestCounters::B>(), 0);
    EXPECT_EQ(counters.get<TestCounters::C>(), 0);
    EXPECT_EQ(counters.get<TestCounters::C>(), 0);
    EXPECT_EQ(counters.get<TestCounters::A>().Name(), "A");
    EXPECT_EQ(counters.get<TestCounters::B>().Name(), "B");
    EXPECT_EQ(counters.get<TestCounters::C>().Name(), "C");
    EXPECT_EQ(counters.get<TestCounters::TestCounterD>().Name(), "TestCounterD");
}


DEFINE_COUNTERS(TestCountersForReset, A, B, C);

TEST(DefineCounters, Reset)
{
    TestCountersForReset counters;
    counters.get<counters.A>() = 10;
    counters.get<counters.B>() = 100;
    counters.get<counters.C>() = 1000;
    EXPECT_EQ(counters.get<counters.A>(), 10);
    EXPECT_EQ(counters.get<counters.B>(), 100);
    EXPECT_EQ(counters.get<counters.C>(), 1000);
    counters.Reset();
    EXPECT_EQ(counters.get<counters.A>(), 0);
    EXPECT_EQ(counters.get<counters.B>(), 0);
    EXPECT_EQ(counters.get<counters.C>(), 0);
}

} // namespace anonymous
