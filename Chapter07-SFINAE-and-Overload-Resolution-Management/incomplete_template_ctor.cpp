class Base {
public:
    Base()
        : i_()
    {
    }
    virtual void increment(long v) { i_ += v; }

private:
    long i_;
};

template <typename T>
class Derived : public T {
public:
    Derived()
        : T()
        , j_()
    {
    }
    Derived(long i, long j)
        : T(i)
        , j_(j)
    {
    }
    void increment(long v)
    {
        j_ += v;
        T::increment(v);
    }

private:
    long j_;
};

int main()
{
    Derived<Base> d;
    d.increment(5);
}
