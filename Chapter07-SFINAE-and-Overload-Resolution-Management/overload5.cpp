#include <iostream>

void f(int i, int j) { std::cout << "f(int, int)" << std::endl; }

template <typename T>
void f(T i, T *p)
{
    std::cout << "f(T, T*)" << std::endl;
}

void f(...) { std::cout << "f(...)" << std::endl; }

int main()
{
    f(5, 5); // f(int, int)
    int i;
    f(5, &i); // f(T, T*)
    // This compiles but uses the ... overload
    // template deduction fails because 5l deduces T as long, &i deduces T as int
    f(5l, &i);      // f(...)
    f<int>(5l, &i); // f(T, T*)
    // This forces the template overload, but does not compile because &i is int* and not long*.
    // f<long>(5l, &i);
}
