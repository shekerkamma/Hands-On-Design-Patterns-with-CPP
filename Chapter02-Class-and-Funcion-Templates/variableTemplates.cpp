#include <iostream>

template <typename T>
constexpr T pi = T(3.14159265358979323846264338327950288419716939937510582097494459230781L);

int main(int argc, char const* argv[])
{

    std::cout << pi<float> << std::endl; // 3.14159
    std::cout << pi<double> << std::endl; // 3.14159 - Unexpected!

    return 0;
}
