#include <iostream>

namespace implementation {
template <typename C>
static char test(int C::*); // selected if C is a class type

template <typename C>
static int test(...); // selected otherwise
} // namespace implementation

template <class T>
struct is_class : std::integral_constant<bool, sizeof(implementation::test<T>(NULL)) == sizeof(char)> {
};

struct A {
};

int main()
{
    static_assert(!is_class<int>::value, "int is a class?");
    static_assert(is_class<A>::value, "A is not a class?");

    std::cout << std::boolalpha << "Int is class: " << is_class<int>::value << std::endl;
    std::cout << std::boolalpha << "A is class: " << is_class<A>::value << std::endl;
}
