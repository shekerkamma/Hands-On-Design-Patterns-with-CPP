#include <iostream>

template <typename T>
void f(T)
{
    std::cout << "sizeof f(T): " << sizeof(T::i) << std::endl;
}

void f(...)
{
    std::cout << "f(...)" << std::endl;
}

struct A {
    typedef int t;
    t i;
};

int main()
{
    // This does not compile:
    // SFINAE does not suppress errors in the body of the function!
    // First template is used and leads to compilation error: ‘i’ is not a member of ‘int’
    // f(0);

    A a { 5 };
    f(a); // sizeof f(T): 4
}
