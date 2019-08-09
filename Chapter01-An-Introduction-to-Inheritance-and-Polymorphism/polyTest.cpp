// Polymorphism and virtual functions
// p. 54

#include <iostream>

class Base {
public:
    virtual void f() { std::cout << "Base::f()" << std::endl; }
    void g() { f(); }
};

class Derived : private Base {
    // private:
    void f() override { std::cout << "Derived::f()" << std::endl; }

public:
    void h() { g(); }
    // void f() override { std::cout << "Derived::f()" << std::endl; }
};

int main(int argc, char const* argv[])
{
    Derived d;
    d.h(); // Prints "Derived::f()"
    // d.f();

    return 0;
}
