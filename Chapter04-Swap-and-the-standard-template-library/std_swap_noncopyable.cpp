#include <utility>
#include <iostream>

class A
{
public:
    explicit A(int i) : i_(i) {}
    A(const A &rhs) = delete;
    A &operator=(const A &rhs) = delete;
    int i_;
};

int main()
{
    A a1(1), a2(2);
    std::cout << "\nInitial:" << std::endl;
    std::cout << "a1: " << a1.i_ << " a2: " << a2.i_ << std::endl;

#if 0
    // Class A does not have a copy constructor nor a move constructor. Will not compile!
    std::swap(a1, a2);  // Not the best way
    std::cout << "\nAfter swap:" << std::endl;
    std::cout << "a1: " << a1.i_ << " a2: " << a2.i_ << std::endl;
#endif
}
