// Version 01 with deletion policy.
#include <cstdlib>
#include <cassert>
#include <iostream>

// Signature of call-operator is the same for all deletion policies: void operator()(T *p) const

template <typename T>
struct DeleteByOperator
{
    void operator()(T *p) const
    {
        delete p;
    }
};

template <typename T>
struct DeleteByFree
{
    void operator()(T *p) const
    {
        p->~T();
        free(p);
    }
};

template <typename T>
struct DeleteDestructorOnly
{
    void operator()(T *p) const
    {
        p->~T();
    }
};

class SmallHeap
{
public:
    SmallHeap() {}
    ~SmallHeap() {}
    void *allocate(size_t s)
    {
        assert(s <= size_);
        return mem_;
    }
    void deallocate(void *p)
    {
        assert(p == mem_);
    }

private:
    static constexpr size_t size_ = 1024;
    char mem_[size_];
    SmallHeap(const SmallHeap &) = delete;
    SmallHeap &operator=(const SmallHeap &) = delete;
};
void *operator new(size_t s, SmallHeap *h) { return h->allocate(s); }

template <typename T>
struct DeleteSmallHeap
{
    explicit DeleteSmallHeap(SmallHeap &heap)
        : heap_(heap) {}
    void operator()(T *p) const
    {
        p->~T();
        heap_.deallocate(p);
    }

private:
    SmallHeap &heap_;
};

typedef void (*delete_int_t)(int *);
void delete_int(int *p) { delete p; }

template <typename T>
void delete_T(T *p) { delete p; }

template <typename T, typename DeletionPolicy = DeleteByOperator<T>>
class SmartPtr
{
public:
    explicit SmartPtr(T *p = nullptr,
                      // Why is this deletion_policy a reference?
                      // Why is it DeletionPolicy() and not just DeletionPolicy? Is this template instantiation? No.
                      // -> DeletionPolicy object is just default constructed. Most of the deletion policies examples
                      // are structs. Except the function delete_int(int *p) and delete_T(T *p).
                      // const DeletionPolicy &deletion_policy = DeletionPolicy()) : p_(p),
                      const DeletionPolicy deletion_policy = DeletionPolicy()) : p_(p),
                                                                                 deletion_policy_(deletion_policy)
    {
    }
    ~SmartPtr()
    {
        deletion_policy_(p_);
    }
    void release() { p_ = nullptr; }

    T *operator->() { return p_; } // reference operator
    const T *operator->() const { return p_; }

    T &operator*() { return *p_; } // content operator
    const T &operator*() const { return *p_; }

private:
    T *p_;
    DeletionPolicy deletion_policy_;
    // Delete copy constructor and assignment operator.
    SmartPtr(const SmartPtr &) = delete;
    SmartPtr &operator=(const SmartPtr &) = delete;
};

int main()
{
    {
        SmartPtr<int> p(new int(42));
        std::cout << *p << std::endl;
    }

    {
        SmallHeap h;
        SmartPtr<int, DeleteSmallHeap<int>> q{new (&h) int(42), DeleteSmallHeap<int>(h)};
        std::cout << *q << std::endl;
    }

    {
        SmartPtr<int, delete_int_t> p(new int(42), delete_int);
        std::cout << *p << std::endl;
    }

    {
        // This does not work. delete_t<int> is not a type but a function.
        // The second param to SmartPtr is always something callable.
        // SmartPtr<int, delete_T<int>> p(new int(42), delete_T<int>);
        // std::cout << *p << std::endl;
    }

    {
        // C++17
        // This compiles if you make deletion_policy not a reference in the constructor of SmartPtr.
        // See also p. 551 where the issue of const& is discussed.
        SmartPtr p(new int(42), delete_T<int>);
        std::cout << *p << std::endl;
    }

    {
        SmartPtr<int, delete_int_t> p(new int(42), delete_T<int>);
        std::cout << *p << std::endl;
    }

    {
        // C++17
        // This compiles if you make deletion_policy not a reference in the constructor of SmartPtr.
        SmartPtr p(new int(42), delete_int);
        std::cout << *p << std::endl;
    }

    {
        class C
        {
            // ...
        };

        class D
        {
            // ...
        };

        // Does not compile:
        // SmartPtr<C, DeleteByOperator<D>> p(new C);
        // SmartPtr<int, DeleteByOperator<double>> p(new int{42});
    }
}
