#include <deque>
#include <iostream>
#include <typeinfo>
#include <vector>

template <typename T>
class ArrayOf2 {
public:
    T& operator[](size_t i) { return a_[i]; }
    const T& operator[](size_t i) const { return a_[i]; }
    T sum() const { return a_[0] + a_[1]; }

private:
    T a_[2];
};

template <typename T, size_t N>
class Array {
public:
    T& operator[](size_t i)
    {
        if (i >= N) {
            throw std::out_of_range("Bad index");
        }
        return data_[i];
    };

private:
    T data_[N];
};

// Here is a function template that has two template template parameters:
template <template <typename, typename> class Out_container,
    template <typename, typename> class In_container,
    typename T>
Out_container<T, std::allocator<T>> resequence(const In_container<T, std::allocator<T>>& in_container)
{
    Out_container<T, std::allocator<T>> out_container;
    for (auto x : in_container) {
        out_container.push_back(x);
    }
    return out_container;
};

template <typename N, typename D>
class Ratio {
public:
    Ratio()
        : num_()
        , denom_()
    {
    }
    Ratio(const N& num, const D& denom)
        : num_(num)
        , denom_(denom)
    {
    }
    explicit operator double() const
    {
        return double(num_) / double(denom_);
    }

private:
    N num_;
    D denom_;
};

// Explicit specialization
// Completely independent of original template.
// You can write whatever code you feel like.
template <>
class Ratio<double, double> // Both template type parameters are specified to be double.
{
public:
    Ratio()
        : value_()
    {
    }

    // Member functions can also be templated
    template <typename N, typename D>
    Ratio(const N& num, const D& denom)
        : value_(static_cast<double>(num) / static_cast<double>(denom))
    {
    }

    explicit operator double() const { return value_; }

private:
    double value_;
};

// Partial specialization
template <typename D>
class Ratio<double, D> {
public:
    Ratio()
        : value_()
    {
    }
    Ratio(const double& num, const D& denom)
        : value_(num / static_cast<double>(denom))
    {
    }
    explicit operator double() const { return value_; }

private:
    double value_;
};

// Another partial specialization
template <typename N>
class Ratio<N, double> {
public:
    Ratio()
        : value_()
    {
    }
    Ratio(const N& num, const double& denom)
        : value_(static_cast<double>(num) / denom)
    {
    }
    explicit operator double() const { return value_; }

private:
    double value_;
};

// Now we use pointers.
template <typename N, typename D>
class Ratio<N*, D*> {
public:
    Ratio(N* num, D* denom)
        : num_(num)
        , denom_(denom)
    {
    }
    explicit operator double() const
    {
        return static_cast<double>(*num_) / static_cast<double>(*denom_);
    }

private:
    N* const num_;
    D* const denom_;
};

// Explicit specialization of a member function.
template <>
Ratio<float, float>::operator double() const
{
    return num_ / denom_;
}

// Declaration, but no definition
template <typename T>
class Value;

// Still specializations possible
template <typename T>
class Value<T*> {
public:
    explicit Value(T* p)
        : v_(*p)
    {
    }

private:
    T v_;
};

template <typename T>
class Value<T&> {
public:
    explicit Value(T& p)
        : v_(p)
    {
    }

private:
    T v_;
};

int main(int argc, char const* argv[])
{
    {
        ArrayOf2<int> i;
        i[0] = 1;
        i[1] = 5;
        std::cout << i.sum() << std::endl; // 6

        ArrayOf2<double> x;
        x[0] = -3.5;
        x[1] = 4;
        std::cout << x.sum() << std::endl; // 0.5

        ArrayOf2<char*> c;
        char s[] = "Hello";
        c[0] = s;
        c[1] = s + 2;
        std::cout << c[0] << std::endl;
        std::cout << c[1] << std::endl;
        // Does not compile! But the whole thing compiles when you don't use sum().
        // c.sum();

        Array<int, 5> a; // OK
        // std::cin >> a[0];
        // std::cout << a[0] << std::endl;
        // Array<int, a[0]> b; // Error: expressions must have a CONSTANT value. Size of array must be known at compile time.
    }

    {
        std::vector<int> v { 1, 2, 3, 4, 5 };
        auto d = resequence<std::deque>(v); // deque with 1, 2, 3, 4, 5
        for (auto item : d) {
            std::cout << item << ' ';
        }
        std::cout << std::endl
                  << "------------------------" << std::endl;

        Ratio<int, double> r1;
        Ratio r2 { 1, 2.0 };
        std::cout << static_cast<double>(r2) << std::endl;
    }

    {
        int i = 5;
        double x = 10;
        auto r { Ratio(&i, &x) };
        std::cout << static_cast<double>(r) << std::endl; // 0.5
        x = 2.5;
        std::cout << static_cast<double>(r) << std::endl; // 2
    }

    {
        int i = 5;
        int* p = &i;
        int& r = i;
        Value<int*> v1(p); // T* specialization
        Value<int&> v2(r); // T& specialization
        // Value<int> v2(i); // Does not compile
    }

    return 0;
}
