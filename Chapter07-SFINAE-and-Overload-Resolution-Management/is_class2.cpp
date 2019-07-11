#include <iostream>

template <typename T>
class is_class
{
    template <typename C>
    static char test(int C::*); // selected if C is a class type

    template <typename C>
    static int test(...); // selected otherwise

public:
    // Old syntax:
    //enum { value = sizeof(test<T>(NULL)) == 1 };

    // sizeof return value of used template function:
    // Mostly, but not guaranteed: sizeof(char) = 1, sizeof(int) = 4. (See later examples.)
    static constexpr bool value = sizeof(test<T>(NULL)) == 1;
};

struct A
{
};

int main()
{
    std::cout << is_class<int>::value << std::endl;
    std::cout << is_class<A>::value << std::endl;
}
