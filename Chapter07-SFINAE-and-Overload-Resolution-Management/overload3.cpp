#include <iostream>

void f(int i) { std::cout << "f(int)" << std::endl; }

template <typename T>
void f(T i)
{
    std::cout << "f(T)" << std::endl;
}

template <typename T>
void f(T* i)
{
    std::cout << "f(T*)" << std::endl;
}

int main()
{
    int i = 0;
    void* p = &i;
    f(5); // f(int)
    f(5l); // f(T)
    f(&i); // f(T*)
    f(NULL); // f(T)!
    f(nullptr); // f(T)!
    f(p); // f(T*)
}
