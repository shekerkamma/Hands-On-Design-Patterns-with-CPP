#include <iostream>

class Empty1
{
};

class Empty2
{
};

class Derived : private Empty1, private Empty2
{
    int i;
};

class Composed
{
    int i;
    Empty1 e1;
    Empty2 e2;
};

int main(int argc, char const *argv[])
{
    std::cout << "Empty: " << sizeof(Empty1) << "\nDerived: " << sizeof(Derived) << "\nComposed: " << sizeof(Composed) << std::endl;

    return 0;
}
