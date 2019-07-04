#include <iostream>

// Using fold expression
template <typename... T>
auto sum(const T &... x)
{
    return (x + ...);
}

// Using recursion
template <typename T>
auto sum1(const T &x1)
{
    return x1;
}

template <typename T1, typename... T>
auto sum1(const T1 &x1, const T &... x)
{
    return x1 + sum(x...);
}

// Variadic class template

// A class template, Group, that can hold any number of objects of different types
// and return the right object when it's converted to one of the types it holds.

// General template only declared, not defined.
template <typename... T>
struct Group;

// Base case of recursion
template <typename T>
struct Group<T>
{
    T t_;
    Group() = default;
    // Copy constructor
    explicit Group(const T &t) : t_(t) {}
    // Move constructor
    explicit Group(T &&t) : t_{std::move(t)} {}
    // Cast operators
    explicit operator const T &() const { return t_; }
    explicit operator T &() { return t_; }
};

// General recursion case
template <typename T1, typename... T>
struct Group<T1, T...> : Group<T...>
{
    T1 t1_;
    Group() = default;
    explicit Group(const T1 &t1, T &&... t) : Group<T...>(std::forward<T>(t)...), t1_(t1) {}
    explicit Group(T1 &&t1, T &&... t) : Group<T...>(std::forward<T>(t)...), t1_(std::move(t1)) {}
    explicit operator const T1 &() const { return t1_; }
    explicit operator T1 &() { return t1_; }
};

template <typename... T>
auto makeGroup(T &&... t)
{
    return Group<T...>(std::forward<T>(t)...);
}

int main(int argc, char const *argv[])
{
    {
        std::cout << sum(5, 7, 3) << std::endl;    // 15, int
        std::cout << sum(5, 7, 3) << std::endl;    // 15, int
        std::cout << sum(5, 7L, 3) << std::endl;   // 15, long
        std::cout << sum(5, 7L, 2.9) << std::endl; // 14.9, double
    }

    {
        std::cout << "------------------" << std::endl;

        std::cout << sum1(5, 7, 3) << std::endl;    // 15, int
        std::cout << sum1(5, 7, 3) << std::endl;    // 15, int
        std::cout << sum1(5, 7L, 3) << std::endl;   // 15, long
        std::cout << sum1(5, 7L, 2.9) << std::endl; // 14.9, double
    }

    {
        std::cout << "------------------" << std::endl;

        Group<int, long> g(3, 5);
        std::cout << static_cast<int>(g) << std::endl;  // 3
        std::cout << static_cast<long>(g) << std::endl; // 5
    }

    {
        std::cout << "------------------" << std::endl;

        auto g = makeGroup(3, 2.2, std::string("xyz"));
        std::cout << int(g) << std::endl;         // 3
        std::cout << double(g) << std::endl;      // 2.2
        std::cout << std::string(g) << std::endl; // "xyz"
    }

    return 0;
}
