# Count 
Macro for easy counter definitions.
Use the macro to define a new class name and one or more counter names.
The macro will produce a class with the provided name.  The counters will
be part of an enum defined inside the class.  
The main method get<>() retrieves a Count::Counter object corresponding to
the counter enum via the template parameter.
Each Count::Counter object will contain the counter name as a std::string
and the value of the counter.
A template variable for the counter enum value is used so the code can
perform static asserts and ensure no out-of-bounds access to the underlying
container.
```
class CounterClassName
{
    enum CounterEnum { /* Provided Counter Names */ };
    using Counter_t = Count::Counter<unsigned long long>;
    size_t Size() const;
    void Reset();
    template<CounterEnum index> Counter_t& get();
}
```
## Usage
```
DEFINE_COUNTERS(CounterClassName, CounterName1, CounterName2, ..., CounterNameN)
```
## Example
```
DEFINE_COUNTERS(TestCounters, A, B, C)
TestCounters counters;
counters.get<TestCounters::A>() = 2;
counters.get<TestCounters::B>()++;
auto c = counters.get<TestCounters::C>();
std::cout << "Counter: " << c.Name() << "=" << c.Value();
```
