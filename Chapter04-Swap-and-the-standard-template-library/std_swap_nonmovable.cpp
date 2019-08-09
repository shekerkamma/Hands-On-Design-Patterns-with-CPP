#include <iostream>
#include <utility>

class A {
public:
    explicit A(int i)
        : i_(i)
    {
    }
    A(const A& rhs)
        : i_(rhs.i_)
    {
        std::cout << "A(const A&)" << std::endl;
    }
    A(const A&& rhs) = delete;
    A& operator=(const A& rhs)
    {
        i_ = rhs.i_;
        std::cout << "A = A&" << std::endl;
        return *this;
    }
    A& operator=(const A&& rhs) = delete;
    int i_;
};

int main()
{
    A a1(1), a2(2);
    std::cout << "\nInitial:" << std::endl;
    std::cout << "a1: " << a1.i_ << " a2: " << a2.i_ << std::endl;

#if 0
    // Note that if the class has copy operations declared and
    // move operations declared as deleted, there is no automatic fallback to
    // copying — that class is a non-movable type and std::swap() will not compile
    // for it:
    std::swap(a1, a2);
    std::cout << "\nAfter swap:" << std::endl;
    std::cout << "a1: " << a1.i_ << " a2: " << a2.i_ << std::endl;
#endif
}
