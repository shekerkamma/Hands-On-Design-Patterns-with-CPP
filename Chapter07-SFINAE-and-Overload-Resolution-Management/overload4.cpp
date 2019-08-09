#include <iostream>

void f(int i) { std::cout << "f(int)" << std::endl; }
void f(...) { std::cout << "f(...)" << std::endl; }

struct A {
};

struct B {
    operator int() const { return 0; }
};

int main()
{
    A a;
    B b;

    f(5); // f(int)
    f(5l); // f(int)
    f(5.0); // f(int)
    f(a); // f(...)
    f(b); // f(int)
}
