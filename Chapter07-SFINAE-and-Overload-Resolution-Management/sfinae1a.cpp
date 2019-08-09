#include <iostream>

template <typename T>
void f(typename T::t& i)
{
    std::cout << "f(T::t)" << std::endl;
}

template <typename T>
void f(T i)
{
    std::cout << "f(T)" << std::endl;
}

struct A {
    struct t {
        int i;
    };
    t i;
};

int main()
{
    A a { 5 };

    f<A>(a.i); // f(T::T)
    f<int>(5); // f(T)
    f(a.i); // f(T)
    f(5); // f(T)
}
