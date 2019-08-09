#include <iostream>

class Base {
public:
    Base()
        : i_()
    {
    }

    virtual void increment(long v) { i_ += v; }

    // private:
    long i_;
};

template <typename T>
class Derived : public T {
public:
    Derived()
        : T()
        , j_()
    {
    }

    void increment(long v)
    {
        j_ += v;
        T::increment(v);
    }

    // This will not compile if we try to call it but is OK by itself.
    void multiply(long v)
    {
        j_ *= v;
        // There is no T::multiply() for Base:
        T::multiply(v);
    }

    // private:
    long j_;
};

int main()
{
    Derived<Base> d;
    d.increment(5);
    // Will not compile:
    // d.multiply(12);

    std::cout << d.i_ << std::endl;
    std::cout << d.j_ << std::endl;
}
