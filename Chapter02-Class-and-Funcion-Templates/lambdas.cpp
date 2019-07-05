#include <iostream>
#include <algorithm>
#include <vector>

void f(int i){};

struct G
{
    void operator()(int i){};
};

// compare() is too far away (in real code) from sort in do_work()
bool compare(int i, int j) { return i < j; }

void do_work()
{
    std::vector<int> v;
    //.....
    std::sort(v.begin(), v.end(), compare);
}

// compare() close, but too verbose
void do_work1()
{
    std::vector<int> v;
    //.....
    struct compare
    {
        bool operator()(int i, int j) const { return i < j; }
    };

    std::sort(v.begin(), v.end(), compare());
}

// lambda expressions are the solution
void do_work2()
{
    std::vector<int> v;
    // .....
    auto compare = [](int i, int j) { return i < j; };
    std::sort(v.begin(), v.end(), compare);
}

// OMG, way too complicated
// In local classes, we are not allowed to reference variables from the containing scope,
// except by passing them through the constructor arguments.
void do_work3()
{
    std::vector<double> v;
    // .....
    struct compare_with_tolerance
    {
        const double tolerance;
        explicit compare_with_tolerance(double tol) : tolerance(tol) {}
        bool operator()(double x, double y) const
        {
            return x < y && std::abs(x - y) > tolerance;
        }
    };
    double tolerance = 0.01;
    std::sort(v.begin(), v.end(), compare_with_tolerance(tolerance));
}

// For the lambda expressions, the compiler automatically generates a constructor
// to capture all local variables mentioned in the body of the expres sion
void do_work4()
{
    std::vector<double> v;
    // .....
    double tolerance = 0.01;
    // We can declare the arguments as auto, which effectively makes the operator() of the
    // lambda expression a template.
    auto compare_with_tolerance = [=](auto x, auto y) {
        return x < y && std::abs(x - y) > tolerance;
    };
    std::sort(v.begin(), v.end(), compare_with_tolerance);
}

// The general case is declared, but not defined (as ususal).
template <typename... F>
struct overload_set;

// overload_set inherits from the lambda expression
template <typename F1>
struct overload_set<F1> : public F1
{
    overload_set(F1 &&f1) : F1(std::move(f1)) {}
    overload_set(const F1 &f1) : F1(f1) {}
    // Adds function call operator of lamda expression to public interface of overload_set class.
    using F1::operator();
};

template <typename F1, typename... F>
struct overload_set<F1, F...> : public F1, public overload_set<F...>
{
    overload_set(F1 &&f1, F &&... f) : F1(std::move(f1)), overload_set<F...>(std::forward<F>(f)...) {}
    overload_set(const F1 &f1, F &&... f) : F1(f1), overload_set<F...>(std::forward<F>(f)...) {}
    using F1::operator();
};

// constructs the overload set from any number of lambda expressions
// Not a convenience, we need type deduction!
// Helper function deduces the types of all lambda expressions.
template <typename... F>
auto overload(F &&... f)
{
    return overload_set<F...>(std::forward<F>(f)...);
}

// using parameter packs (pp) (C++17)
// The variadic template inherits directly from the parameter pack. 
template <typename... F>
struct overload_set_pp : public F...
{
    overload_set_pp(F &&... f) : F(std::forward<F>(f))... {}
    using F::operator()...; // C++17
};

// Helper function for parameter packs not needed, actually.
template <typename... F>
auto overload_pp(F &&... f)
{
    return overload_set_pp<F...>(std::forward<F>(f)...);
}

int main(int argc, char const *argv[])
{
    {
        f(5); // Function
        G g;
        g(5); // Functor
    }

    {
        int i = 5;
        double d = 7.3;
        // Now we can overload lambda expression!
        auto l = overload(
            [](int *i) { std::cout << "i=" << *i << std::endl; },
            [](double *d) { std::cout << "d=" << *d << std::endl; });

        l(&i); // i=5
        l(&d); // d=5.3
    }

    {
        std::cout << "------------------" << std::endl;

        int i = 5;
        double d = 7.3;
        // Now we can overload lambda expression!
        // Helper function overload_pp() not needed but of course still works.
        auto l = overload_set_pp(
            [](int *i) { std::cout << "i=" << *i << std::endl; },
            [](double *d) { std::cout << "d=" << *d << std::endl; });

        l(&i); // i=5
        l(&d); // d=5.3
    }

    return 0;
}
