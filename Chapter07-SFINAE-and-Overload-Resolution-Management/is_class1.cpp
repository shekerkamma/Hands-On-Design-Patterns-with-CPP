#include <iostream>

struct A {
};

template <typename T>
void f(A T::*) // Could be a member pointer to anything int, long, double, float, and as here custom class A. Although A is empty!
{
    std::cout << "T is a class" << std::endl;
}

template <typename T>
void f(...)
{
    std::cout << "T is not a class" << std::endl;
}

int main()
{
    f<int>(1.0); // No type deduction. Type is int. But there is no int::* (not valid syntax). So first template is eliminated.
    f<int>(0); // Argument does not matter as second template is used. Argument is variadic. Does not matter at run-time - not used.
    f<int>('a'); // Argument does not matter.
    f<int>(NULL); // Argument does not matter.
    f<A>(0); // Type is A. There exists A::* as valid syntax. So first template is used.
    f<A>(nullptr); // Type is A. There exists A::* as valid syntax. So first template is used.
    f<A>(1000); // 1000 is an int and not a pointer. -> "T is not a class."
}
