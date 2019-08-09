#include <iostream>
#include <typeinfo>
#include <utility>
#include <vector>

template <typename T>
T increment(T x)
{
    return x + 1;
}

template <typename T>
T sum(T from, T to, T step)
{
    T res = from;
    while ((from += step) < to) {
        res += from;
    }
    return res;
}

template <typename T>
T half(T x)
{
    return x / 2;
}

template <typename U, typename V>
U half1(V x)
{
    return x / 2;
}

template <typename T>
T Max(T x, T y)
{
    return (x > y) ? x : y;
}

template <typename T>
T decrement(T* p)
{
    return --(*p);
}

template <typename T>
T first(const std::vector<T>& v)
{
    return v[0];
}

// template <typename U, typename V>
// std::pair<V, U> swap12(const std::pair<U, V> &x)
// {
// return std::pair<V, U>(x.second, x.first);
// }

// Easier.
template <typename U, typename V>
auto swap12(const std::pair<U, V>& x)
{
    return std::make_pair(x.second, x.first);
}

template <typename T>
auto swap12(const T& x)
{
    return std::make_pair(x.second, x.first);
}

template <typename T>
T do_something(T x)
{
    return ++x;
}

// Explicit specialization of a template function.
template <>
double do_something<double>(double x)
{
    return x / 2;
}

// But you cannot change the signature or in this caste the return value of the template.
// template <>
// long do_something<int>(int x)
// {
// return x + x;
// }

template <typename T>
void whatami(T* x)
{
    std::cout << x << " is pointer" << std::endl;
}

// References declared with “&&” that may be either lvalue references or rvalue references
// may bind to anything. Such unusually flexible references deserve their own name.
// Scott Meyer calls them universal references.
template <typename T>
void whatami(T&& x)
{
    std::cout << "Something weird" << std::endl;
}

void whatami(int x) { std::cout << x << " is int" << std::endl; }
void whatami(long x) { std::cout << x << " is long" << std::endl; }
void whatami(double x) { std::cout << x << " is double" << std::endl; }

// This is a variadic function, not a variadic template.
// As long as we have the overload whatami(T&& x) available, the variadic func‐
// tion will never be the preferred overload, at least not for any calls to
// whatami() with one argument. Without that template, whatami(...) is called for
// any argument that is not a number or a pointer.
// You cam check that by commenting out whatami(T&& x).
void whatami(...)
{
    std::cout << "It's something or somethings" << std::endl;
}

int main(int argc, char const* argv[])
{
    {
        char c[] { "This is a string." };

        std::cout << increment(5) << std::endl;
        std::cout << increment(5.2) << std::endl;
        std::cout << increment(c) << std::endl;

        std::cout << sum(1, 10, 1) << std::endl;
        std::cout << sum(1.0, 10.9, 1.1) << std::endl;

        std::cout << "------------------" << std::endl;
    }

    {
        int i1 = half<int>(5);
        double x1 = half<double>(5);
        auto i2 = half(5);
        auto x2 = half(5.0);
        std::cout << i1 << std::endl;
        std::cout << x1 << std::endl;
        std::cout << i2 << std::endl;
        std::cout << x2 << std::endl;
        std::cout << half(5) << std::endl;
        std::cout << half(5.0) << std::endl;

        long x = 10;
        unsigned int y = 15;
        auto z = half(x + y); // z is  a long.
        std::cout << z << " is a " << typeid(z).name() << std::endl;

        // Return a double.
        auto y1 = half1<double>(8);
        std::cout << y1 << " is a " << typeid(y1).name() << std::endl;
    }

    {
        // Error: no matching function for call to ‘Max(long int, int)’
        // Compiler does not deduce 11 to be a long int. 11 could be a lot of other
        // types. Compiler does not find all possible types for 11. There could be a lot, actually.

        // auto x3 = Max(7L, 11);
    }

    std::cout << "------------------" << std::endl;

    {
        int i = 7;
        // Deduced type of T will be int.
        decrement(&i); // i == 6
        std::cout << i << std::endl;
    }

    {
        std::vector<int> v { 11, 25, 67 };
        std::cout << first(v) << std::endl; // T is int, returns 11

        auto [first, second] = swap12(std::make_pair(7, 4.2)); // pair of 4.2, 7
        std::cout << first << ' ' << second << std::endl;
    }

    {
        std::cout << "------------------" << std::endl;

        std::cout << do_something(3) << std::endl; // 4
        std::cout << do_something(3.0) << std::endl; // 1.5
    }

    {
        std::cout << "------------------" << std::endl;

        whatami(5L); // 5 is long
        whatami(5); // 5 is int
        // whatami(5.0); // Compilation error
        int i = 5;
        whatami(i); // 5 is int
        whatami(&i); // 0x???? is a pointer

        class C {
            // .....
        };

        C c;
        whatami(&c); // 0x???? is a pointer
        whatami(c); // Something weird
    }

    {
        std::cout << "------------------" << std::endl;

        int i = 5;
        float x = 4.2;
        whatami(i); // i is int
        whatami(x); // Something weird
    }
    return 0;
}
