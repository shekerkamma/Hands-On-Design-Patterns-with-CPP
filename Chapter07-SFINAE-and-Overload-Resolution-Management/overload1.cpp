#include <iostream>

void f(int i) { std::cout << "f(int)" << std::endl; }
void f(long i) { std::cout << "f(long)" << std::endl; }
void f(double i) { std::cout << "f(double)" << std::endl; }

int main()
{
    f(5);
    f(5l);
    f(5.0);
    f(5.0f);
    {
        std::cout << "----------------" << std::endl;
        // Ambigious:
        // f(5u);
        unsigned int i = 5u;
        f(static_cast<int>(i));
        f(static_cast<long>(i));
        f(static_cast<double>(i));
    }
}
