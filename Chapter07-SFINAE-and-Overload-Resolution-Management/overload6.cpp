#include <iostream>

void f(int i, int j = 0) { std::cout << "f(int, int)" << std::endl; }

template <typename T>
void f(T i, T* p = NULL)
{
    std::cout << "f(T, T*)" << std::endl;
}

void f(...) { std::cout << "f(...)" << std::endl; }

int main()
{
    int i;
    f(5); // f(int, int)
    f(5l); // f(T, T*)
    f(5, &i); // f(T, T*)
    f(5l, &i); // f(...)
}
